echo $(which clang++)
sleep 2

clang++ -std=c++20 -o main \
    main.cpp \
    banking/models.cpp \
    banking/services.cpp \
    banking/withdrawal.cpp \
    database/data_mappers.cpp \
    database/encryption.cpp \
    database/managers.cpp \
    database/services.cpp \
    location/models.cpp \
    location/services.cpp \
    registration/models.cpp \
    registration/services.cpp \
