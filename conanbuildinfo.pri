CONAN_INCLUDEPATH += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/include" \
    "/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/include"
CONAN_LIBS += -lcurl -lz
CONAN_SYSTEMLIBS += 
CONAN_FRAMEWORKS += -framework CoreFoundation -framework Security
CONAN_FRAMEWORK_PATHS += 
CONAN_LIBDIRS += -L"/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/lib" \
    -L"/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/lib"
CONAN_BINDIRS += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/bin"
CONAN_RESDIRS += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/res"
CONAN_BUILDDIRS += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/" \
    "/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/"
CONAN_DEFINES += "CURL_STATICLIB=1"
CONAN_QMAKE_CXXFLAGS += 
CONAN_QMAKE_CFLAGS += 
CONAN_QMAKE_LFLAGS_SHLIB += 
CONAN_QMAKE_LFLAGS_APP += 

CONAN_INCLUDEPATH_LIBCURL += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/include"
CONAN_LIBS_LIBCURL += -lcurl
CONAN_SYSTEMLIBS_LIBCURL += 
CONAN_FRAMEWORKS_LIBCURL += -framework CoreFoundation -framework Security
CONAN_FRAMEWORK_PATHS_LIBCURL += 
CONAN_LIBDIRS_LIBCURL += -L"/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/lib"
CONAN_BINDIRS_LIBCURL += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/bin"
CONAN_RESDIRS_LIBCURL += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/res"
CONAN_BUILDDIRS_LIBCURL += "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15/"
CONAN_DEFINES_LIBCURL += "CURL_STATICLIB=1"
CONAN_QMAKE_CXXFLAGS_LIBCURL += 
CONAN_QMAKE_CFLAGS_LIBCURL += 
CONAN_QMAKE_LFLAGS_SHLIB_LIBCURL += 
CONAN_QMAKE_LFLAGS_APP_LIBCURL += 
CONAN_LIBCURL_ROOT = "/Users/simcenter/.conan/data/libcurl/7.72.0/_/_/package/3d1bec21b16e6b00e50fed264612d3520d664d15"

CONAN_INCLUDEPATH_ZLIB += "/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/include"
CONAN_LIBS_ZLIB += -lz
CONAN_SYSTEMLIBS_ZLIB += 
CONAN_FRAMEWORKS_ZLIB += 
CONAN_FRAMEWORK_PATHS_ZLIB += 
CONAN_LIBDIRS_ZLIB += -L"/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/lib"
CONAN_BINDIRS_ZLIB += 
CONAN_RESDIRS_ZLIB += 
CONAN_BUILDDIRS_ZLIB += "/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc/"
CONAN_DEFINES_ZLIB += 
CONAN_QMAKE_CXXFLAGS_ZLIB += 
CONAN_QMAKE_CFLAGS_ZLIB += 
CONAN_QMAKE_LFLAGS_SHLIB_ZLIB += 
CONAN_QMAKE_LFLAGS_APP_ZLIB += 
CONAN_ZLIB_ROOT = "/Users/simcenter/.conan/data/zlib/1.2.12/_/_/package/e4fbacdee83eb1a2e68227ffe19f6e9a61b36cbc"

CONFIG(conan_basic_setup) {
    INCLUDEPATH += $$CONAN_INCLUDEPATH
    LIBS += $$CONAN_LIBS
    LIBS += $$CONAN_LIBDIRS
    BINDIRS += $$CONAN_BINDIRS
    DEFINES += $$CONAN_DEFINES
    CONFIG(release, debug|release) {
        INCLUDEPATH += $$CONAN_INCLUDEPATH_RELEASE
        LIBS += $$CONAN_LIBS_RELEASE
        LIBS += $$CONAN_LIBDIRS_RELEASE
        BINDIRS += $$CONAN_BINDIRS_RELEASE
        DEFINES += $$CONAN_DEFINES_RELEASE
    } else {
        INCLUDEPATH += $$CONAN_INCLUDEPATH_DEBUG
        LIBS += $$CONAN_LIBS_DEBUG
        LIBS += $$CONAN_LIBDIRS_DEBUG
        BINDIRS += $$CONAN_BINDIRS_DEBUG
        DEFINES += $$CONAN_DEFINES_DEBUG
    }
    LIBS += $$CONAN_SYSTEMLIBS
    CONFIG(release, debug|release) {
        LIBS += $$CONAN_SYSTEMLIBS_RELEASE
    } else {
        LIBS += $$CONAN_SYSTEMLIBS_DEBUG
    }
    LIBS += $$CONAN_FRAMEWORKS
    LIBS += $$CONAN_FRAMEWORK_PATHS
    CONFIG(release, debug|release) {
        LIBS += $$CONAN_FRAMEWORKS_RELEASE
        LIBS += $$CONAN_FRAMEWORK_PATHS_RELEASE
    } else {
        LIBS += $$CONAN_FRAMEWORKS_DEBUG
        LIBS += $$CONAN_FRAMEWORK_PATHS_DEBUG
    }
    QMAKE_CXXFLAGS += $$CONAN_QMAKE_CXXFLAGS
    QMAKE_CFLAGS += $$CONAN_QMAKE_CFLAGS
    QMAKE_LFLAGS_SHLIB += $$CONAN_QMAKE_LFLAGS_SHLIB
    QMAKE_LFLAGS_APP += $$CONAN_QMAKE_LFLAGS_APP
    QMAKE_CXXFLAGS_DEBUG += $$CONAN_QMAKE_CXXFLAGS_DEBUG
    QMAKE_CFLAGS_DEBUG += $$CONAN_QMAKE_CFLAGS_DEBUG
    QMAKE_LFLAGS_SHLIB_DEBUG += $$CONAN_QMAKE_LFLAGS_SHLIB_DEBUG
    QMAKE_LFLAGS_APP_DEBUG += $$CONAN_QMAKE_LFLAGS_APP_DEBUG
    QMAKE_CXXFLAGS_RELEASE += $$CONAN_QMAKE_CXXFLAGS_RELEASE
    QMAKE_CFLAGS_RELEASE += $$CONAN_QMAKE_CFLAGS_RELEASE
    QMAKE_LFLAGS_SHLIB_RELEASE += $$CONAN_QMAKE_LFLAGS_SHLIB_RELEASE
    QMAKE_LFLAGS_APP_RELEASE += $$CONAN_QMAKE_LFLAGS_APP_RELEASE
}