cmake_minimum_required(VERSION 3.5)
project(gifteos VERSION 0.1.0)

find_package(eosio.cdt)

add_contract(nft nft ${CMAKE_CURRENT_SOURCE_DIR}/src/nft.cpp)
add_contract(game game ${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp)

target_include_directories(nft.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(game.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
