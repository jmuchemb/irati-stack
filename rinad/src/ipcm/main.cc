/*
 * IPC Manager
 *
 *    Francesco Salvestrini <f.salvestrini@nextworks.it>
 *    Vincenzo Maffione <v.maffione@nextworks.it>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 */

#include <cstdlib>
#include <iostream>
#include <map>

#include <librina/common.h>

#include "common/options.h"


class EventLoopData {
 public:
        virtual ~EventLoopData() { }
};

class EventLoop {
 public:
        typedef void (*EventHandler)(rina::IPCEvent *event, EventLoopData *);

        void register_event(rina::IPCEventType type, EventHandler handler);
        void run();

        EventLoop(EventLoopData *dm) : data_model(dm) { }
 private:
        std::map<rina::IPCEventType, EventHandler> handlers;
        EventLoopData *data_model;

};

void
EventLoop::register_event(rina::IPCEventType type, EventHandler handler)
{
        handlers[type] = handler;
}

void
EventLoop::run()
{
        for (;;) {
                rina::IPCEvent *event = rina::ipcEventProducer->eventWait();
                rina::IPCEventType ty;

                if (!event) {
                        std::cerr << "Null event received" << std::endl;
                        break;
                }

                ty = event->getType();
                if (handlers.count(ty) && handlers[ty]) {
                        handlers[ty](event, data_model);
                }
        }
}

class IPCManager : public EventLoopData {
 public:
        int fake;
};

static void FlowAllocationRequestedEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void AllocateFlowRequestResultEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void AllocateFlowResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void FlowDeallocationRequestedEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void DeallocateFlowResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void ApplicationUnregisteredEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void FlowDeallocatedEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void ApplicationRegistrationRequestEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void RegisterApplicationResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void ApplicationUnregistrationRequestEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void UnregisterApplicationResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void ApplicationRegistrationCanceledEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void AssignToDifRequestEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void AssignToDifResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void UpdateDifConfigRequestEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void UpdateDifConfigResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void EnrollToDifRequestEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void EnrollToDifResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void NeighborsModifiedNotificaitonEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessDifRegistrationNotificationHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessQueryRibHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void GetDifPropertiesHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void GetDifPropertiesResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void OsProcessFinalizedHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcmRegisterAppResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcmUnregisterAppResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcmDeallocateFlowResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcmAllocateFlowRequestResultHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void QueryRibResponseEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessDaemonInitializedEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void TimerExpiredEventHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessCreateConnectionResponseHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessUpdateConnectionResponseHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessCreateConnectionResultHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessDestroyConnectionResultHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

static void IpcProcessDumpFtResponseHandler(rina::IPCEvent *event, EventLoopData *dm)
{
}

int main(int argc, char * argv[])
{
        IPCManager *ipcm = new IPCManager();
        EventLoop loop(ipcm);

        (void) argc;
        (void) argv;

        rina::initialize("test", "/tmp/test");

        loop.register_event(rina::FLOW_ALLOCATION_REQUESTED_EVENT,
                        FlowAllocationRequestedEventHandler);
        loop.register_event(rina::ALLOCATE_FLOW_REQUEST_RESULT_EVENT,
                        AllocateFlowRequestResultEventHandler);
        loop.register_event(rina::ALLOCATE_FLOW_RESPONSE_EVENT,
                        AllocateFlowResponseEventHandler);
        loop.register_event(rina::FLOW_DEALLOCATION_REQUESTED_EVENT,
                        FlowDeallocationRequestedEventHandler);
        loop.register_event(rina::DEALLOCATE_FLOW_RESPONSE_EVENT,
                        DeallocateFlowResponseEventHandler);
        loop.register_event(rina::APPLICATION_UNREGISTERED_EVENT,
                        ApplicationUnregisteredEventHandler);
        loop.register_event(rina::FLOW_DEALLOCATED_EVENT,
                        FlowDeallocatedEventHandler);
        loop.register_event(rina::APPLICATION_REGISTRATION_REQUEST_EVENT,
                        ApplicationRegistrationRequestEventHandler);
        loop.register_event(rina::REGISTER_APPLICATION_RESPONSE_EVENT,
                        RegisterApplicationResponseEventHandler);
        loop.register_event(rina::APPLICATION_UNREGISTRATION_REQUEST_EVENT,
                        ApplicationUnregistrationRequestEventHandler);
        loop.register_event(rina::UNREGISTER_APPLICATION_RESPONSE_EVENT,
                        UnregisterApplicationResponseEventHandler);
        loop.register_event(rina::APPLICATION_REGISTRATION_CANCELED_EVENT,
                        ApplicationRegistrationCanceledEventHandler);
        loop.register_event(rina::ASSIGN_TO_DIF_REQUEST_EVENT,
                        AssignToDifRequestEventHandler);
        loop.register_event(rina::ASSIGN_TO_DIF_RESPONSE_EVENT,
                        AssignToDifResponseEventHandler);
        loop.register_event(rina::UPDATE_DIF_CONFIG_REQUEST_EVENT,
                        UpdateDifConfigRequestEventHandler);
        loop.register_event(rina::UPDATE_DIF_CONFIG_RESPONSE_EVENT,
                        UpdateDifConfigResponseEventHandler);
        loop.register_event(rina::ENROLL_TO_DIF_REQUEST_EVENT,
                        EnrollToDifRequestEventHandler);
        loop.register_event(rina::ENROLL_TO_DIF_RESPONSE_EVENT,
                        EnrollToDifResponseEventHandler);
        loop.register_event(rina::NEIGHBORS_MODIFIED_NOTIFICAITON_EVENT,
                        NeighborsModifiedNotificaitonEventHandler);
        loop.register_event(rina::IPC_PROCESS_DIF_REGISTRATION_NOTIFICATION,
                        IpcProcessDifRegistrationNotificationHandler);
        loop.register_event(rina::IPC_PROCESS_QUERY_RIB,
                        IpcProcessQueryRibHandler);
        loop.register_event(rina::GET_DIF_PROPERTIES,
                        GetDifPropertiesHandler);
        loop.register_event(rina::GET_DIF_PROPERTIES_RESPONSE_EVENT,
                        GetDifPropertiesResponseEventHandler);
        loop.register_event(rina::OS_PROCESS_FINALIZED,
                        OsProcessFinalizedHandler);
        loop.register_event(rina::IPCM_REGISTER_APP_RESPONSE_EVENT,
                        IpcmRegisterAppResponseEventHandler);
        loop.register_event(rina::IPCM_UNREGISTER_APP_RESPONSE_EVENT,
                        IpcmUnregisterAppResponseEventHandler);
        loop.register_event(rina::IPCM_DEALLOCATE_FLOW_RESPONSE_EVENT,
                        IpcmDeallocateFlowResponseEventHandler);
        loop.register_event(rina::IPCM_ALLOCATE_FLOW_REQUEST_RESULT,
                        IpcmAllocateFlowRequestResultHandler);
        loop.register_event(rina::QUERY_RIB_RESPONSE_EVENT,
                        QueryRibResponseEventHandler);
        loop.register_event(rina::IPC_PROCESS_DAEMON_INITIALIZED_EVENT,
                        IpcProcessDaemonInitializedEventHandler);
        loop.register_event(rina::TIMER_EXPIRED_EVENT,
                        TimerExpiredEventHandler);
        loop.register_event(rina::IPC_PROCESS_CREATE_CONNECTION_RESPONSE,
                        IpcProcessCreateConnectionResponseHandler);
        loop.register_event(rina::IPC_PROCESS_UPDATE_CONNECTION_RESPONSE,
                        IpcProcessUpdateConnectionResponseHandler);
        loop.register_event(rina::IPC_PROCESS_CREATE_CONNECTION_RESULT,
                        IpcProcessCreateConnectionResultHandler);
        loop.register_event(rina::IPC_PROCESS_DESTROY_CONNECTION_RESULT,
                        IpcProcessDestroyConnectionResultHandler);
        loop.register_event(rina::IPC_PROCESS_DUMP_FT_RESPONSE,
                        IpcProcessDumpFtResponseHandler);

        loop.run();

        return EXIT_SUCCESS;
}
