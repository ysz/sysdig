/*
Copyright (C) 2013-2018 Draios Inc dba Sysdig.

This file is part of sysdig.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.

*/
//
// k8s_pod_handler.h
//

#pragma once

#include "json/json.h"
#include "sinsp_auth.h"
#include "k8s_handler.h"
#include "k8s_component.h"

class sinsp;

class k8s_pod_handler : public k8s_handler
{
public:
	k8s_pod_handler(k8s_state_t& state
#ifdef HAS_CAPTURE
		,ptr_t dependency_handler
		,collector_ptr_t collector = nullptr
		,std::string url = ""
		,const std::string& http_version = "1.1"
		,ssl_ptr_t ssl = 0
		,bt_ptr_t bt = 0
		,bool connect = true
		,bool blocking_socket = false
#endif // HAS_CAPTURE
		);

	~k8s_pod_handler();

	static std::vector<std::string> extract_pod_container_ids(const Json::Value& item);
	static k8s_container::list extract_pod_containers(const Json::Value& item);
	static void extract_pod_data(const Json::Value& item, k8s_pod_t& pod);
	static size_t extract_pod_restart_count(const Json::Value& item);

private:
	static std::string EVENT_FILTER;
	static std::string STATE_FILTER;

	virtual bool handle_component(const Json::Value& json, const msg_data* data = 0);
};
