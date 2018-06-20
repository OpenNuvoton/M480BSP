#include "SimpleHOGP_Gap.h"
#include "SimpleHOGP_Gap_Adv.h"
#include "bt.h"
#include "ble_gap.h"
#include <stdio.h>
#include <string.h>
#include "sys/param.h"
/******************************************************************************/
/*Defines                                                                     */
/******************************************************************************/
#define ALWAYS_USE_UNDIR
#define ALWAYS_USE_NORMAL_UNDIR
#define CONN_INTERVAL 8
#define SLAVE_LATENCY 29

/******************************************************************************/
/*Variable                                                                     */
/******************************************************************************/
SimpleHOGP_Gap_Status gap_status = {0, SIMPLE_NOT_INITED, 0};
static uint8_t pub_address[6];
static ble_addr_t ble_bonded_peer;
static uint16_t ble_conn_handle;
static uint16_t ble_conn_interval = 100;
static uint16_t ble_slave_latency;
static ble_addr_t ble_current_peer;
static uint8_t deviceName[30] = "Nuvoton Simple HID"; //default name

/******************************************************************************/
/*Static function                                                             */
/******************************************************************************/
static void SimpleHOGP_check_bt_bonding(void)
{
    gap_status.is_bonded = BLE_gap_sm_get_last_paired_device(&ble_bonded_peer);

    printf("check bt bonding: %s.\n", (gap_status.is_bonded) ? " bonded" :"not bonded");
}

static void SimpleHOGP_ble_adv_scan_cb(bool isuccess, uint8_t err_code)
{
    printf("set scan data %s\n", isuccess ? "ok" : "fail");

    if(isuccess)
    {
        SimpleHOGP_Gap_State_Set(SIMPLE_IDLE);

        //BT_Log_Enable(0);

    }
    else
    {
        SimpleHOGP_Gap_State_Set(SIMPLE_INIT_FAIL);
    }
}


static void SimpleHOGP_ble_set_pub_addr_cb(bool isuccess, uint8_t err_code)
{

    uint8_t len;
    uint8_t ad[31] =
    {
        0x0B, 0x09, 'N', 'u', 'v', 'o', 't', 'o', 'n', 'H', 'I', 'D'
    };

    len = strlen((char *)deviceName);
    ad[0] = len + 1;
    ad[1] = 0x09;
    memcpy(ad+2, deviceName, len);

    printf("set rand address %s\n", isuccess ? "ok" : "fail");

    ble_gap_scan_data_set(ad, sizeof(ad), SimpleHOGP_ble_adv_scan_cb);
}

static bool SimpleHOGP_update_connection_interval(void)
{
    static uint8_t noise = 0;

    ble_gap_conn_params_t conn =
    {
        CONN_INTERVAL, CONN_INTERVAL,
        SLAVE_LATENCY + (noise++&0x03),
        MIN(CONN_INTERVAL*(SLAVE_LATENCY+1), 0xC80),
        0, 0
    };

    if(ble_gap_conn_param_update(ble_conn_handle, &conn))
    {
        printf("invalid connection handle, connection might be disconnected already \n");
        return false;
    }
    else
    {
        printf("negotiating connection interval\n");
        return true;
    }
}


/*event handler callback*/
static void SimpleHOGP_bt_inited_handler(bt_evt_t *evt)
{
    if(evt->evt.misc_evt.param.inited.is_success)
    {
        ble_addr_t addr;

        addr.addr_type = ble_addr_type_public;

        memcpy(addr.addr, pub_address, 6);

        ble_gap_address_set(&addr, SimpleHOGP_ble_set_pub_addr_cb);

    }
    else
    {
        printf("***************** BT init fail*********************\n");
        while(1);
    }
}

static void SimpleHOGP_connection_complete_handler(bt_evt_t *evt)
{
    ble_gap_evt_connected_t* p = &evt->evt.gap_evt.params.connected;

    if(p->status)
    {
        printf("failed to connected with directed advertising\n");
        printf("dir_adv_TO, switch to bonded undir adv \n");
        SimpleHOGP_bonded_undir_adv();
        return;
    }

    ble_conn_handle = p->conn_handle;
    ble_slave_latency = p->connLatency;
    ble_conn_interval = p->connInterval;

    printf("\n\t+---------BLE connected. Dump connection parameter:---------+\n");
    printf("\t| Connection handle   | 0x%04X                              |\n", ble_conn_handle);
    printf("\t| Peer address        | %02X:%02X:%02X:%02X:%02X:%02X                   |\n",p->peer_addr.addr[5],p->peer_addr.addr[4],p->peer_addr.addr[3],p->peer_addr.addr[2],p->peer_addr.addr[1],p->peer_addr.addr[0]);
    printf("\t| Peer address type   | %s                              |\n", (p->peer_addr.addr_type==0)?"Public":"Random");
    printf("\t| Connection interval | %5d (unit:1.25ms)                 |\n",ble_conn_interval);
    printf("\t| Slave latency:      | %5d                               |\n",ble_slave_latency);
    printf("\t| Supervision timeout | %5d (unit:  10ms)                 |\n",p->supervisionTimeout);
    printf("\t+---------End of BLE connection parameter information ------+\n\n");

    SimpleHOGP_Gap_State_Set(SIMPLE_CONNECTED);

    ble_current_peer = evt->evt.gap_evt.params.connected.peer_addr;

    if(gap_status.is_bonded)
    {
        printf("This device is bonded.\n");
        SimpleHOGP_update_connection_interval();
    }
}

static void SimpleHOGP_connection_disconnect_handler(bt_evt_t *evt)
{

    SimpleHOGP_Gap_State_Set(SIMPLE_IDLE);
    gap_status.link_encrypted = false;

    if(1)
    {
        uint8_t *bd = ble_current_peer.addr;
        printf("BLE device disconnected: reason = 0x%X \n",evt->evt.gap_evt.params.disconnected.reason);
        printf("type = %d ,addr = %02X:%02X:%02X:%02X:%02X:%02X\n",ble_current_peer.addr_type,bd[0],bd[1],bd[2],bd[3],bd[4],bd[5]);
    }

    if(gap_status.is_bonded)
    {
        printf("peer device already bonded, do nothing\n");
    }
    else
    {
        printf("peer device not bonded yet, send ADV_IND again\n");
        SimpleHOGP_normal_undir_adv();
    }
}

static void SimpleHOGP_connection_parm_update_handler(bt_evt_t *evt)
{
    ble_gap_evt_conn_param_update_t* p = &evt->evt.gap_evt.params.conn_param_update;

    if(p->status)
    {
        printf("Connection update rejected.\n");
    }
    else
    {
        ble_slave_latency = p->slave_latency;
        ble_conn_interval = p->conn_interval;

        printf("\n\t+~~~~~BLE connection parameter updated. Dump parameter:~~~~~+\n");
        printf("\t| Connection handle   | 0x%04X                              |\n", ble_conn_handle);
        printf("\t| Connection interval | %5d (unit:1.25ms)                 |\n",ble_conn_interval);
        printf("\t| Slave latency:      | %5d                               |\n",ble_slave_latency);
        printf("\t| Supervision timeout | %5d (unit:  10ms)                 |\n",p->conn_sup_timeout);
        printf("\t+~~~~~~~~ End of BLE connection parameter information ~~~~~~+\n\n");
    }
}

static void SimpleHOGP_sm_set_security_param(void)
{
    ble_sm_security_param_t sm_param =
    {
        SM_IO_NO_INPUT_NO_OUTPUT,       //uint8_t ioCapability;
        SM_OOB_DATA_NOT_PRESENT,        //uint8_t oobDataFlag;  //need to check SM_OOB_SUPPORTED
        SM_BONDING,                     //uint8_t authReqFlag; Bonding_Flag:2, MITM:1, SC:1, Keypress:1, Reserved:3
        16,                             //uint8_t encKeySize;
        0x03,                           //uint8_t keyDistr;
        0x07,                           //uint8_t respKeyDistr;
    };

    BLE_gap_sm_set_security_param(ble_conn_handle, BLE_SM_STATUS_SUCCESS, &sm_param);
}

static void SimpleHOGP_connection_security_update(bt_evt_t *evt)
{
    if(evt->evt.sm_evt.params.conn_sec_update.status == 0)
    {
        gap_status.link_encrypted = true;
        printf("link encrypted!!\n");

    }
    else
        printf("security update fail\n");
}

static void SimpleHOGP_auth_status_update(bt_evt_t *evt)
{
    SimpleHOGP_check_bt_bonding();
}


/******************************************************************************/
/*Public function                                                             */
/******************************************************************************/
void SimpleHOGP_bt_evt_hdl(bt_evt_t *evt)
{
    switch(evt->evt_id)
    {
    case BT_MISC_EVENT_INITED:
        SimpleHOGP_bt_inited_handler(evt);
        break;
    case BLE_GAP_EVT_CONNECTED:
        SimpleHOGP_connection_complete_handler(evt);
        break;
    case BLE_GAP_EVT_DISCONNECTED:
        SimpleHOGP_connection_disconnect_handler(evt);
        break;
    case BLE_GAP_EVT_CONNECT_PARM_UPDATE:
        SimpleHOGP_connection_parm_update_handler(evt);
        break;
    case BLE_SM_EVT_SET_SEC_PARAM_REQUEST:
        SimpleHOGP_sm_set_security_param();
        break;
    case BLE_SM_EVT_CONN_SEC_UPDATE:
        SimpleHOGP_connection_security_update(evt);
        break;
    case BLE_SM_EVT_AUTH_STATUS:
        SimpleHOGP_auth_status_update(evt);
        break;
    case BLE_GATT_EVT_MTU_EXCHANGED:
        printf("\nMTU exchanged to %3d\n",evt->evt.gatt_evt.gatt.mtu_exchanged.new_mtu);
        break;
    }
}


void SimpleHOGP_Gap_Init(uint8_t addr[6], char *name)
{
    uint8_t len;
    memcpy(pub_address, addr, 6);
    SimpleHOGP_check_bt_bonding();

    /*copy device name*/
    len = strlen(name);
    if(len > 29)
        len = 29;
    memcpy(deviceName, name, len);
    deviceName[len] = 0;
}

void SimpleHOGP_Gap_Enter_Adv(void)
{
    if(SimpleHOGP_Gap_State_Get() == SIMPLE_IDLE)
    {
        if(gap_status.is_bonded)
        {
            printf("bonded \n");
#ifdef ALWAYS_USE_NORMAL_UNDIR
            SimpleHOGP_normal_undir_adv();
#else
#ifdef ALWAYS_USE_UNDIR
            SimpleHOGP_bonded_undir_adv();
#else
            SimpleHOGP_dir_adv();
#endif
#endif
        }
        else
        {
            printf("not bonded \n");

            SimpleHOGP_normal_undir_adv();
        }
    }
}

ble_addr_t * SimpleHOGP_Gap_Get_BondedPeer(void)
{
    return &ble_bonded_peer;
}

uint8_t *SimpleHOGP_Gap_GetDeviceName(void)
{
    return deviceName;
}
