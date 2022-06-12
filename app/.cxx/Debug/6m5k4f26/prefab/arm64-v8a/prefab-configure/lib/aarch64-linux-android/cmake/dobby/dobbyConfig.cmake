if(NOT TARGET dobby::dobby)
add_library(dobby::dobby STATIC IMPORTED)
set_target_properties(dobby::dobby PROPERTIES
    IMPORTED_LOCATION "/data/data/com.itsaky.androidide/files/framework/.gradle/caches/transforms-3/9ad8da2816cf4306737b8c03d915911d/transformed/dobby-1.2/prefab/modules/dobby/libs/android.arm64-v8a/libdobby.a"
    INTERFACE_INCLUDE_DIRECTORIES "/data/data/com.itsaky.androidide/files/framework/.gradle/caches/transforms-3/9ad8da2816cf4306737b8c03d915911d/transformed/dobby-1.2/prefab/modules/dobby/include"
    INTERFACE_LINK_LIBRARIES ""
)
endif()

