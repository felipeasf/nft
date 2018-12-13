cmake_minimum_required(VERSION 3.5)
project(bndes_poc VERSION 1.0.0)

find_package(eosio.cdt)

add_contract(nft nft ${CMAKE_CURRENT_SOURCE_DIR}/src/nft.cpp)

target_include_directories(nft.wasm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
