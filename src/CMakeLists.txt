cmake_minimum_required(VERSION 3.6.0)
project(play C)

set(CMAKE_C_STANDARD 99)

add_subdirectory(Common)
add_subdirectory(Persistence)
add_subdirectory(View)
add_subdirectory(Service)


set(SOURCE_FILES TTMS.c Persistence/EntityKey_Persist.c Persistence/EntityKey_Persist.h Persistence/Play_Persist.c Persistence/Play_Persist.h Service/Play.c Service/Play.h View/Play_UI.c View/Play_UI.h Common/List.h Common/common.h Common/common.c Service/EntityKey.c Service/EntityKey.h Persistence/Account_Persist.c Persistence/Account_Persist.h Persistence/Query_Persist.c Persistence/Query_Persist.h Persistence/Sale_Persist.c Persistence/Sale_Persist.h Persistence/SalesAnalysis_Persist.c Persistence/SalesAnalysis_Persist.h Persistence/Schedule_Persist.c Persistence/Schedule_Persist.h Persistence/Seat_Persist.c Persistence/Seat_Persist.h Persistence/Studio_Persist.c Persistence/Studio_Persist.h Persistence/Ticket_Persist.c Persistence/Ticket_Persist.h Service/Account.c Service/Account.h Service/Sale.c Service/Sale.h Service/SalesAnalysis.c Service/SalesAnalysis.h Service/Schedule.c Service/Schedule.h Service/Studio.c Service/Studio.h Service/Ticket.c Service/Ticket.h View/Account_UI.c View/Account_UI.h View/MaiAccount_UI.c View/MaiAccount_UI.h View/Main_Menu.c View/Main_Menu.h View/Sale_UI.c View/Sale_UI.h View/SalesAnalysis_UI.c View/SalesAnalysis_UI.h View/Schedule_UI.c View/Schedule_UI.h View/Seat_UI.c View/Seat_UI.h View/StaSales_UI.c View/StaSales_UI.h View/Studio_UI.c View/Studio_UI.h View/Ticket_UI.c View/Ticket_UI.h)

add_executable(ttms ${SOURCE_FILES})
aux_source_directory(. CPP_LIST)


target_link_libraries(ttms Common Persistence Service View)