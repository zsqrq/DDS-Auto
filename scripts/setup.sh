#！/bin/bash

script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
production_root_path=$(dirname "$script_path")
PATH=$script_path/../thirdparty/Fast-DDS-Gen/scripts:$script_path/../thirdparty/protobuf/bin:$PATH
LD_LIBRARY_PATH=$script_path/../production/lib:$script_path/../thirdparty/protobuf/lib:$LD_LIBRARY_PATH
echo -e "\033[36m Start Building Project at time : $script_path \033[0m \n"
export PATH LD_LIBRARY_PATH
