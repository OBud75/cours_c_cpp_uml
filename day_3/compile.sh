echo $(which clang++)
sleep 2

clang++ -std=c++20 -o main \
    -I/usr/local/include/opencv4 \
    -Wno-deprecated-anon-enum-enum-conversion \
    main.cpp location/location.cpp location/graph.cpp location/tsp.cpp \
    -L/usr/local/lib \
    -lopencv_core -lopencv_imgproc -lopencv_highgui -lopencv_imgcodecs

# echo $(which clang++)
# sleep 2

# clang++ -std=c++20 -o main \
#     main.cpp \
#     banking/models.cpp \
#     banking/services.cpp \
#     banking/withdrawal.cpp \
#     database/data_mappers.cpp \
#     database/encryption.cpp \
#     database/managers.cpp \
#     database/services.cpp \
#     location/models.cpp \
#     location/services.cpp \
#     location/graph.cpp \
#     location/tsp.cpp \
#     registration/models.cpp \
#     registration/services.cpp \
