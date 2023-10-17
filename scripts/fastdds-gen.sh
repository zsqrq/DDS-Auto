#！/bin/bash
script_path="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
PATH=$script_path/../thirdparty/Fast-DDS-Gen/scripts:$PATH
echo -e "\033[36m Start Building Project at time : $script_path \033[0m \n"
export PATH
