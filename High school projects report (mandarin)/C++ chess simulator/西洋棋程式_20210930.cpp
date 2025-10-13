#include <bits/stdc++.h>
using namespace std;
int main () {
	//e2 e4 e7 e5 f1 c4 b8 c6 d1 h5 g8 f6 h5 f7 e8 f7 c4 f7
	string board[8][8] =   //產生棋盤 
	{{".r.", ".n.", ".b.", ".q.", ".k.", ".b.", ".n.", ".r."},
	 {".p.", ".p.", ".p.", ".p.", ".p.", ".p.", ".p.", ".p."},
	 {"###", "   ", "###", "   ", "###", "   ", "###", "   "},
	 {"   ", "###", "   ", "###", "   ", "###", "   ", "###"},
	 {"###", "   ", "###", "   ", "###", "   ", "###", "   "},
	 {"   ", "###", "   ", "###", "   ", "###", "   ", "###"},
	 {"|P|", "|P|", "|P|", "|P|", "|P|", "|P|", "|P|", "|P|"},
	 {"|R|", "|N|", "|B|", "|Q|", "|K|", "|B|", "|N|", "|R|"}};
	for (int i = 0; i < 8; i ++) {
		cout << 8 - i << " ";
		for (int j = 0; j < 8; j++) {
			cout << board[i][j];
		}
		cout << '\n';
	}
	cout << "   a  b  c  d  e  f  g  h" << '\n' << '\n';
	
	string chess_piece1, chess_piece2, chess_piece3;
	bool flag1, turn = false, w_castle1 = true, w_castle2 = true, b_castle1 = true, b_castle2 = true;
	int  x1, y1, x2, y2, win = 0, w_ep = 8, b_ep = 8;
	
	while (1) {
		while (1) { 
			if (turn) {
			cout << "..現在輪到黑棋.." << '\n' << '\n';
			} else {
				cout <<"||現在輪到白棋||" << '\n' << '\n';
			}
			cout << "請輸入要移動的棋子座標 -> ";   //輸入要移動的棋子座標 
			cin >> chess_piece1;
			if (chess_piece1 == "認輸") {
				win = !turn + 1;
				break;
			} else if (chess_piece1 == "和棋"){
				if (turn) {
					cout << "白方是否接受和棋 -> ";
				} else {
					cout << "黑方是否接受和棋 -> ";
				}
				cin >> chess_piece1;
				if (chess_piece1 == "是") {
					win = 3;
					break;
				} else {
					cout << '\n';
					continue;
				}
			}
			y1 = 8 - chess_piece1[1] + '0';
			x1 = chess_piece1[0] - 'a';
			if (y1 < 0 || y1 > 7 || x1 < 0 || x1 > 7) {
				cout << "@ 請輸入[a~h][1~8]" << '\n' << '\n';
			} else {
				chess_piece1 = board[y1][x1];
				if (chess_piece1[0] == '|' && !turn || chess_piece1[0] == '.' && turn) {
				    break;
			    } else {
			    	if (turn) {
			    		cout << "@ 請移動任意[黑棋]" << '\n' << '\n';
			    	} else {
			    		cout << "@ 請移動任意[白棋]" << '\n' << '\n';
				    }
				}
		    }
		}
		if (win != 0) break;
		while (1) {
			cout << "請輸入移動棋子後的座標 -> ";   // 輸入移動棋子後的座標 
			cin >> chess_piece2;
			y2 = 8 - chess_piece2[1] + '0';
			x2 = chess_piece2[0] - 'a';
			if (y2 < 0 || y2 > 7 || x2 < 0 || x2 > 7) {
				cout << "@ 請輸入[a~h][1~8]" << '\n' << '\n';
			} else {
				chess_piece2 = board[y2][x2];
				break;
			}
		}
		
		flag1 = false;
		if (turn && chess_piece2[0] != '.' || !turn && chess_piece2[0] != '|') {    //判斷棋子移動是否合理 
			if (chess_piece1[1] == 'R' || chess_piece1[1] == 'r') {
				if (x1 == x2 || y1 == y2) {
					for (int i = 1; i < abs(x1 - x2 + y1 - y2); i++) {
						if (x1 == x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1];
						} else if (x1 == x2 && y1 > y2) {
							chess_piece3 = board[y1 - i][x1];
						} else if (x1 < x2 && y1 == y2) {
							chess_piece3 = board[y1][x1 + i];
						} else {
							chess_piece3 = board[y1][x1 - i];
						}
						if (chess_piece3[0] == '|' || chess_piece3[0] == '.') flag1 = true;
					}
				} else flag1 = true;
			} else if (chess_piece1[1] == 'N' || chess_piece1[1] == 'n') {
				flag1 = true;
				if (abs(y1 - y2) == 2 && abs(x1 - x2) == 1 || abs(y1 - y2) == 1 && abs(x1 - x2) == 2) {
					flag1 = false;
				}
			} else if (chess_piece1[1] == 'B' || chess_piece1[1] == 'b') {
				if (abs(y1 - y2) == abs(x1 - x2)) {
					for (int i = 1; i < abs(y1 - y2); i++) {
						if (x1 < x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1 + i];
						} else if (x1 < x2 && y1 > y2) {
							chess_piece3 = board[y1 - i][x1 + i];
						} else if (x1 > x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1 - i];
						} else {
							chess_piece3 = board[y1 - i][x1 - i];
						}
						if (chess_piece3[0] == '|' || chess_piece3[0] == '.') flag1 = true;
					}
				} else flag1 = true;
			} else if (chess_piece1[1] == 'Q' || chess_piece1[1] == 'q') {
				if (x1 == x2 || y1 == y2) {
					for (int i = 1; i < abs(x1 - x2 + y1 - y2); i++) {
						if (x1 == x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1];
						} else if (x1 == x2 && y1 > y2) {
							chess_piece3 = board[y1 - i][x1];
						} else if (x1 < x2 && y1 == y2) {
							chess_piece3 = board[y1][x1 + i];
						} else {
							chess_piece3 = board[y1][x1 - i];
						}
						if (chess_piece3[0] == '|' || chess_piece3[0] == '.') flag1 = true;
					}
				} else if (abs(y1 - y2) == abs(x1 - x2)) {
					for (int i = 1; i < abs(y1 - y2); i++) {
						if (x1 < x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1 + i];
						} else if (x1 < x2 && y1 > y2) {
							chess_piece3 = board[y1 - i][x1 + i];
						} else if (x1 > x2 && y1 < y2) {
							chess_piece3 = board[y1 + i][x1 - i];
						} else {
							chess_piece3 = board[y1 - i][x1 - i];
						}
						if (chess_piece3[0] == '|' || chess_piece3[0] == '.') flag1 = true;
					}
				} else flag1 = true;
			} else if (chess_piece1[1] == 'K' || chess_piece1[1] == 'k') {
				if (abs(y1 - y2) > 1 || abs(x1 - x2) > 1 || abs(y1 - y2) + abs(x1 - x2) == 0) {
					flag1 = true;
				}
			} else if (chess_piece1[1] == 'P' || chess_piece1[1] == 'p') {
				flag1 = true;
				if (y1 + turn * 2 - 1 == y2) {
					
					if (turn) {
						if (x1 - x2 == -1 || x1 - x2 == 1) {
							if (chess_piece2[0] == '|') flag1 = false;
						} else if (x1 == x2 && chess_piece2[0] != '|') {
							flag1 = false;
						}
					} else {
						if (x1 - x2 == -1 || x1 - x2 == 1) {
							if (chess_piece2[0] == '.') flag1 = false;
						} else if (x1 == x2 && chess_piece2[0] != '.') {
							flag1 = false;
						}
					} 
				} else if (x1 == x2) {
					if (y1 == 6 && y1 - 2 == y2) {
						chess_piece3 = board[y1 - 1][x1];
						if (chess_piece3[0] != '|' && chess_piece3[0] != '.') {
							chess_piece3 = board[y1 - 2][x1];
							if (chess_piece3[0] != '.') {
								b_ep = x1;
								flag1 = false;
							}
						}
					} else if (y1 == 1 && y1 + 2 == y2) {
						chess_piece3 = board[y1 + 1][x1];
						if (chess_piece3[0] != '|' || chess_piece3[0] != '.') {
							chess_piece3 = board[y1 + 2][x1];
							if (chess_piece3[0] != '|') {
								w_ep = x1;
								flag1 = false;
							}
						}
					} else flag1 = true;
				} else flag1 = true;
			}
		} else flag1 = true;
		
		if (chess_piece1[1] == 'P' || chess_piece1[1] == 'p') {   //吃過路兵 
			if (turn && y1 == 4 && y2 == 5) {
				if (abs(b_ep - x1) == 1 && b_ep == x2) {
					if ((y1 + x1) % 2 == 0) {
						board[4][b_ep] = "   ";
					} else {
						board[4][b_ep] = "###";
					}
					flag1 = false;
				}
			} else if (!turn && y1 == 3 && y2 == 2) {
				if (abs(w_ep - x1) == 1 && w_ep == x2) {
					if ((y1 + x1) % 2 == 0) {
						board[3][w_ep] = "###";
					} else {
						board[3][w_ep] = "   ";
					}
					flag1 = false;
				}
			}
		} 
		
		if (chess_piece1[1] == 'K' || chess_piece1[1] == 'k') {   //國王易位 
			if (x2 == 6 && y2 == 7) {
				if (board[7][4] == "|K|" && board[7][5] == "###" && board[7][6] == "   " && board[7][7] == "|R|" && w_castle1) {
					board[7][5] = "|R|";
					board[7][7] = "   ";
					flag1 = false;
				}
			} else if (x2 == 2 && y2 == 7) {
				if (board[7][4] == "|K|" && board[7][3] == "###" && board[7][2] == "   " && board[7][1] == "###" && board[7][0] == "|R|" && w_castle2) {
					board[7][3] = "|R|";
					board[7][0] = "   ";
					flag1 = false;
				}
			} else if (x2 == 6 && y2 == 0) {
				if (board[0][4] == ".k." && board[0][5] == "   " && board[0][6] == "###" && board[0][7] == ".r." && b_castle1) {
					board[0][5] = ".r.";
					board[0][7] = "   ";
					flag1 = false;
				}
			} else if (x2 == 2 && y2 == 0) {
				if (board[0][4] == ".k." && board[0][3] == "   " && board[0][2] == "###" && board[0][1] == "   " && board[0][0] == ".r." && b_castle2) {
					board[0][3] = ".r.";
					board[0][0] = "###";
					flag1 = false;
				}
			}
		}
		
		if (flag1) {
			cout << "\\\\ 此移動不符合規則! //" << '\n' << '\n';
			continue;
		}
		
		if ((y1 + x1) % 2 == 0) {    //消失棋子  
			board[y1][x1] = "###";
		} else {
			board[y1][x1] = "   ";
		}
		
		if (chess_piece1[1] == 'P' || chess_piece1[1] == 'p') {   //顯示棋子 
			if (turn && y2 == 7 || !turn && y2 == 0) {
				while (1) {
					cout << "請輸入要變換的棋子(Q/N/R/B) -> ";
					cin >> chess_piece3;
					if (chess_piece3 == "R") {
					    if (turn) {
					    	board[y2][x2] = ".r.";
						} else {
							board[y2][x2] = "|R|";
						}
						break;
					} else if (chess_piece3 == "N") {
						if (turn) {
					    	board[y2][x2] = ".n.";
						} else {
							board[y2][x2] = "|N|";
						}
						break;
					} else if (chess_piece3 == "B") {
						if (turn) {
					    	board[y2][x2] = ".b.";
						} else {
							board[y2][x2] = "|B|";
						}
						break;
					} else if (chess_piece3 == "Q") {
						if (turn) {
					    	board[y2][x2] = ".q.";
						} else {
							board[y2][x2] = "|Q|";
						}
						break;
					} else {
						cout << "@ 輸入[Q/N/R/B]" << '\n' << '\n';
					}
				}
			} else board[y2][x2] = chess_piece1;
	    } else {
	    	if (chess_piece1[1] == 'K') {
				w_castle1 = false;
				w_castle2 = false;
			} else if (chess_piece1[1] == 'R') {
				if (x1 == 7 && y1 == 7) {
					w_castle1 = false;
				} else if (x1 == 0 && y1 == 7) {
					w_castle2 = false;
				}
			} else if (chess_piece1[1] == 'k') {
				b_castle1 = false;
				b_castle2 = false;
			} else if (chess_piece1[1] == 'r') {
				if (x1 == 7 && y1 == 0) {
					b_castle1 = false;
				} else if (x1 == 0 && y1 == 0) {
					b_castle2 = false;
				}
			}
			board[y2][x2] = chess_piece1;
		}
		if (chess_piece1[1] != 'P') b_ep = 8;
		if (chess_piece1[1] != 'p') w_ep = 8;
		
		cout << '\n';   //繪製棋盤 
		if (turn) {
			for (int i = 0; i < 8; i++) {
				cout << 8 - i << " ";
				for (int j = 0; j < 8; j++) {
					cout << board[i][j];
				}
				cout << '\n';
			}	
			cout << "   a  b  c  d  e  f  g  h" << '\n' << '\n';
			turn = false;
		} else {
			for (int i = 0; i < 8; i ++) {
				cout << i + 1 << " ";
				for (int j = 0; j < 8; j++) {
					cout << board[7 - i][7 - j];
				}
				cout << '\n';
			}
			cout << "   h  g  f  e  d  c  b  a" << '\n';
			turn = true;
		}
		
		if (chess_piece2[1] == 'K') {
			win = 2;
			break;
		} else if (chess_piece2[1] == 'k') {
			win = 1;
			break;
		} else cout << '\n';
	}
	cout << '\n';
	if (win == 1) {
		cout << "\\\\ 白方勝利 //";
	} else if (win == 2) {
		cout << "\\\\ 黑方勝利 //";
	} else {
		cout << "\\\\ 雙方平手 //";
	}
	return 0;
}
