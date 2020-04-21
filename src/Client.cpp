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
#include "Client.hpp"

Client::~Client() {
}


void Client::initialize(unsigned int player, unsigned int board_size){
    this -> player = player;
    this -> board_size = board_size;

    string filename;

    if (player == 1) {
        filename = "player_1.action_board.json";
    } else if (player == 2){
        filename = "player_2.action_board.json";
    } else {
        throw ClientWrongPlayerNumberException();
    }

    ofstream boardfile(filename);    //creates file of name filename
    vector<vector<int>> board(board_size, vector<int>(board_size));     //creates vector
    cereal::JSONOutputArchive archive(boardfile);   //creates a writable json archive
    archive(cereal::make_nvp("board", board));  //add object board into json file
}


void Client::fire(unsigned int x, unsigned int y) {
    string filename;

    if (player == 1) {
        filename = "player_1.shot.json";
    } else if (player == 2){
        filename = "player_2.shot.json";
    }

    ofstream boardfile(filename);
    cereal::JSONOutputArchive archive(boardfile);
    archive(cereal::make_nvp("x", x), cereal::make_nvp("y", y));

}


bool Client::result_available() {
    string filename = "player_" + to_string(player) + ".result.json";
    ifstream file(filename);

    if (!file) {
        return false;
    } else {
        return true;
    }
}


int Client::get_result() {
    if(!result_available()) {
        throw ClientException("No result file available.");
    }

    string filename = "player_" + to_string(player) + ".result.json";
    ifstream file(filename);
    cereal::JSONInputArchive filein(file);

    int result;
    filein(result);

    remove(filename.c_str());

    if (result == 0 || result == 1 || result == -1) {
        return result;
    } else {
        throw ClientException("");
    }
}



void Client::update_action_board(int result, unsigned int x, unsigned int y) {
    string filename = "player_" + to_string(player) + ".action_board.json";
    vector<vector<int>> board(board_size, vector<int>(board_size));

    board[y][x] = result;

    ofstream file(filename);
    cereal::JSONOutputArchive outfile(file);
    outfile(cereal::make_nvp("board", board));
}


string Client::render_action_board(){
    string filename = "player_" + to_string(player) + ".action_board.json";
    vector<vector<int>> board(board_size, vector<int>(board_size));

    ifstream input(filename);
    cereal::JSONInputArchive file(input);
    file(cereal::make_nvp("board", board));

    string boardstring;
    for (int i = 0; i < board_size; i++) {
        for (int j = 0; j < board_size; j++) {
            boardstring += to_string(board[i][j]);
        }

        boardstring += "\n";
    }

    return boardstring;
}