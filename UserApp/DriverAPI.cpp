#include "DriverAPI.h"

ULONG DriverAPI::get_client_base(ULONG process_id)
{
    INFO_STRUCT info = { 0 };
    info.code = CLIENT_MODULE_REQUEST;
    info.process_id = process_id;

    Hook::call_hook(&info);

    return info.client_base;
}

ULONG DriverAPI::get_engine_base(ULONG process_id)
{
    INFO_STRUCT info = { 0 };
    info.code = ENGINE_MODULE_REQUEST;
    info.process_id = process_id;

    Hook::call_hook(&info);

    return info.engine_base;
}



