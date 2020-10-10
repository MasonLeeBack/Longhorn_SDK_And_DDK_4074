# Build with split headers - required for some DDK samples
USE_SPLIT_HEADERS=1
C_DEFINES=$(C_DEFINES) -DUSE_SPLIT_HEADERS=1
