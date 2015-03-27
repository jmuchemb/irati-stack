//
// Echo CDAP Server
//
// Bernat Gastón <bernat.gaston@i2cat.net>e>
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
//

#ifndef SERVER_HPP
#define SERVER_HPP

#include <librina/librina.h>
#include <time.h>
#include <signal.h>
#include <librina/cdap_v2.h>

#include "cdap-echo-application.h"

class ConnectionCallback : public rina::cdap::CDAPCallbackInterface
{
 public:
  ConnectionCallback(bool *keep_serving,
                     rina::cdap::CDAPProviderInterface **prov);
  void open_connection(const rina::cdap_rib::con_handle_t &con,
                       const rina::cdap_rib::flags_t &flags, int message_id);
  void remote_read_request(const rina::cdap_rib::con_handle_t &con,
                           const rina::cdap_rib::obj_info_t &obj,
                           const rina::cdap_rib::filt_info_t &filt,
                           int message_id);
  void close_connection(const rina::cdap_rib::con_handle_t &con,
                        const rina::cdap_rib::flags_t &flags, int message_id);
 private:
  bool *keep_serving_;
  rina::cdap::CDAPProviderInterface **prov_;
};

class Server : public Application
{
 public:
  Server(const std::string& dif_name, const std::string& app_name,
         const std::string& app_instance, const int dealloc_wait);
  void run();

 protected:
  void serveEchoFlow(rina::Flow *flow);
  //static void destroyFlow(sigval_t val);
  bool cacep(rina::Flow *flow);
  bool release(rina::Flow *flow, int invoke_id);
 private:
  void startWorker(rina::Flow * f);
  int interval;
  int dw;
};

#endif
