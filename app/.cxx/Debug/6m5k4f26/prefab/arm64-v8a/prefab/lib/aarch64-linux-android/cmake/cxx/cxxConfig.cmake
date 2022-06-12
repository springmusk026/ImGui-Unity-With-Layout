if(NOT TARGET cxx::cxx)
add_library(cxx::cxx STATIC IMPORTED)
set_target_properties(cxx::cxx PROPERTIES
    IMPORTED_LOCATION "/data/data/com.itsaky.androidide/files/framework/.gradle/caches/transforms-3/2e7b15718b035c3e7d50a1a32619a28a/transformed/cxx-1.2.0/prefab/modules/cxx/libs/android.arm64-v8a/libcxx.a"
    INTERFACE_INCLUDE_DIRECTORIES "/data/data/com.itsaky.androidide/files/framework/.gradle/caches/transforms-3/2e7b15718b035c3e7d50a1a32619a28a/transformed/cxx-1.2.0/prefab/modules/cxx/include"
    INTERFACE_LINK_LIBRARIES ""
)
endif()

