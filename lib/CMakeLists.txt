set (BUILD_SHARED ON)
fetch_module_via_branch(lib/msmp ${PROJECT_SOURCE_DIR}/lib/msmp ${PROJECT_SOURCE_DIR} "master")

find_headers(${CMAKE_CURRENT_SOURCE_DIR}/msmp headers)
# set(public_headers ${headers} PARENT_SCOPE)
set(public_headers "\"${PROJECT_SOURCE_DIR}/lib/msmp/source/msmp_api/i_host.hpp\", \
                    \"${PROJECT_SOURCE_DIR}/lib/msmp/source/msmp_api/i_connection.hpp\", \
                    \"${PROJECT_SOURCE_DIR}/lib/msmp/source/msmp_api/tcp/tcp_host.hpp\"" PARENT_SCOPE)
set(include_dirs "\"${PROJECT_SOURCE_DIR}/lib/msmp/lib/eul/include\", \
                    \"${PROJECT_SOURCE_DIR}/lib/msmp/source/msmp_api\"" PARENT_SCOPE)
