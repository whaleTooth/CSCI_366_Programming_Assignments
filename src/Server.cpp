//    Battleship game assignment for MSU CSCI 366
//    Copyright (C) 2020    Mike P. Wittie
//
//    This program is free software: you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation, either version 3 of the License, or
//    (at your option) any later version.
//
//    This program is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with this program.  If not, see <https://www.gnu.org/licenses/>.


#include "common.hpp"
#include "Server.hpp"


/**
 * Calculate the length of a file (helper function)
 *
 * @param file - the file whose length we want to query
 * @return length of the file in bytes
 */
int get_file_length(ifstream *file){
}


void Server::initialize(unsigned int board_size,
                        string p1_setup_board,
                        string p2_setup_board){
    if(board_size != BOARD_SIZE) {
        throw ServerException("Board size not equal.");
    }

    if(p1_setup_board.length() == 0 || p2_setup_board.length() == 0) {
        throw ServerException("No file name.");
    }

    this->board_size = board_size;
}


Server::~Server() {
}


BitArray2D *Server::scan_setup_board(string setup_board_name){
}

int Server::evaluate_shot(unsigned int player, unsigned int x, unsigned int y) {
    if (x < 0 || x > board_size - 1 || y < 0 || y > board_size - 1 ){
        return OUT_OF_BOUNDS;
    }

    if (player > MAX_PLAYERS || player <= 0) {
        throw ServerException("Wrong amount of players.");
    }

    if (player == 1) {
        player = 2;
    } else if (player == 2){
        player = 1;
    } else {
        throw ServerException("Player number invalid.");
    }

    string filename = "player_" + to_string(player) + ".setup_board.txt";
    ifstream setupboard;
    setupboard.open(filename);
    vector<string> line(board_size, " ");

    string fileline;
    int counter = 0;
    while (!setupboard.eof()) {
        while(getline(setupboard, fileline)) {
            line[counter] = fileline;
            counter++;
        }
    }

    char shot = line[y].at(x);      //uses user input to get the location of the shot

    if (shot == '_') {
        return MISS;
    } else {
        return HIT;
    }

}


int Server::process_shot(unsigned int player) {
    if (player <= 0 || player > MAX_PLAYERS){
        throw ServerException("Player number invalid.");
    }

    string shotfilename;
    if (player == 1) {
        shotfilename = "player_1.shot.json";
    } else if (player == 2) {
        shotfilename = "player_2.shot.json";
    }

    ifstream shotfile;//shotfilename);    //create input file stream of filename
    shotfile.open(shotfilename);

    if (!shotfile) {
        return NO_SHOT_FILE;
    }

    int x, y;
    cereal::JSONInputArchive readfile(shotfile);
    readfile(x, y);     //read in x, y values from shot file

    int result = evaluate_shot(player, x, y);   //get value (1, -1, or 0) from evaluate_shot
    remove(shotfilename.c_str());     //remove shotfile

    string resultfilename;
    if (player == 1) {
        resultfilename = "player_1.result.json";
    } else if (player == 2) {
        resultfilename = "player_2.result.json";
    }

    ofstream resultfile(resultfilename);
    cereal::JSONOutputArchive playerresult(resultfile);
    playerresult(cereal::make_nvp("result", result));

    return SHOT_FILE_PROCESSED;
}