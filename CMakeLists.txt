cmake_minimum_required(VERSION 3.29)
project(CardGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(CardGame main.cpp
        Headers/Card.h
        Headers/StandardCard.h
        Headers/BonusCard.h
        Headers/PenaltyCard.h
        Headers/Deck.h
        Headers/Player.h
        Headers/Game.h
        main.cpp)