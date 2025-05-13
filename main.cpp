#include <SFML/Graphics.hpp>
#include <iostream>
#define Length 8
#define BPawn 1
#define WPawn -1
#define BRook 2
#define WRook -2
#define BKnight 3
#define WKnight -3
#define BBishop 4
#define WBishop -4
#define BQueen 5
#define WQueen -5
#define BKing 6
#define WKing -6
using namespace std;
using namespace sf;
struct Position
{
    int x, y;
} Initial, KingWhite, KingBlack, promotionW, promotionB;
int size = 100, move = 0, x, y, rightWR = 0, leftWR = 0, KingW = 0, rightBR = 0,
    leftBR = 0, KingB = 0, isMoving = 0, WCheck = 0, BCheck = 0, Wpromotion = 0,
    Bpromotion = 0, Turn = 0, WFlag = 0, BFlag = 0, enPassantB = -1,
    enPassantW = -1, count4 = 0, count1 = 0, count2 = 0, count3 = 0,
    NoMovedPiece = 0;
bool BenPassant = false, WenPassant = false, Break = false, checkmate = false,
     stalemate = false, menu = false, Bplace = false, Wplace = false,
     Reset = false, draw = true, Bdraw = true, Ldraw = true, Rdraw = true,
     Tdraw = true, buttonVisible = false;
float dx = 0, dy = 0;
int board[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int Simboard[8][8];
int FBoard[8][8];
int Tempboard[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int BSimboard[8][8];
int BFBoard[8][8];
int BTempboard[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int LSimboard[8][8];
int LFBoard[8][8];
int LTempboard[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int RSimboard[8][8];
int RFBoard[8][8];
int RTempboard[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int TSimBoard[8][8];
int TFBoard[8][8];
int TTempBoard[8][8] = {
    2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
    -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
};
int WP(int ix, int iy, int fx, int fy) // White Pawn
{
    if (Initial.y == 6)
    // First pawn movement
    {
        if (fy == iy - 1 && fx == ix && board[iy - 1][ix] == 0)
        {
            return 1;
        }
        else if (fy == iy - 2 && fx == ix && board[iy - 1][ix] == 0 &&
                 board[iy - 2][ix] == 0)
        {
            BenPassant = true;
            enPassantB = ix;
            return 1;
        }
    }
    else if (fy == iy - 1 && fx == ix && board[iy - 1][ix] == 0)
    // one square up
    {
        return 1;
    }
    if (board[iy - 1][ix - 1] > 0)
    // left diagnol capture
    {
        if (fy == iy - 1 && fx == ix - 1)
        {
            return 1;
        }
    }
    if (board[iy - 1][ix + 1] > 0)
    // right diagnol capture
    {
        if (fy == iy - 1 && fx == ix + 1)
        {
            return 1;
        }
    }
    if (iy == 3 && fy == iy - 1 && abs(fx - ix) == 1) // en passant
    {
        if (board[iy][fx] == 1 && enPassantW == fx && WenPassant == true)
        {
            if (board[iy][ix] == 0)
            {
                board[iy][fx] = 0;
                return 1;
            }
        }
    }
    return 0;
}
int BP(int ix, int iy, int fx, int fy) // Black Pawn
{
    if (Initial.y == 1)
    // Initial pawn movement
    {
        if (fy == iy + 1 && fx == ix && board[iy + 1][ix] == 0)
        {
            return 1;
        }
        else if (fy == iy + 2 && fx == ix && board[iy + 1][ix] == 0 &&
                 board[iy + 2][ix] == 0)
        {
            WenPassant = true;
            enPassantW = ix;
            return 1;
        }
    }
    else if (fy == iy + 1 && fx == ix && board[iy + 1][ix] == 0)
    // down 1 square
    {
        return 1;
    }
    if (board[iy + 1][ix - 1] < 0)
    // left diagnol capture
    {
        if (fy == iy + 1 && fx == ix - 1)
        {
            return 1;
        }
    }
    if (board[iy + 1][ix + 1] < 0)
    // right diagnol capture
    {
        if (fy == iy + 1 && fx == ix + 1)
        {
            return 1;
        }
    }
    if (iy == 4 && fy == iy + 1 && abs(fx - ix) == 1) // en passant
    {
        if (board[iy][fx] == -1 && enPassantB == fx && BenPassant == true)
        {
            if (board[iy][ix] == 0)
            {
                board[iy][fx] = 0;
                return 1;
            }
        }
    }
    return 0;
}
int WR(int ix, int iy, int fx, int fy) // White Rook
{
    for (int i = ix - 1; i >= 0; i--)
    // left
    {
        if (board[iy][i] >= 0 && (fx == i && fy == iy))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy - 1; i >= 0; i--)
    // up
    {
        if (board[i][ix] >= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    for (int i = ix + 1; i <= 7; i++)
    // right
    {
        if (board[iy][i] >= 0 && (fy == iy && fx == i))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy + 1; i <= 7; i++)
    // down
    {
        if (board[i][ix] >= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    return 0;
}
int BR(int ix, int iy, int fx, int fy) // Black Rook
{
    for (int i = ix - 1; i >= 0; i--)
    // left
    {
        if (board[iy][i] <= 0 && (fx == i && fy == iy))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy - 1; i >= 0; i--)
    // up
    {
        if (board[i][ix] <= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    for (int i = ix + 1; i <= 7; i++)
    // right
    {
        if (board[iy][i] <= 0 && (fy == iy && fx == i))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy + 1; i <= 7; i++)
    // down
    {
        if (board[i][ix] <= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    return 0;
}
int WB(int ix, int iy, int fx, int fy) // White Bishop
{
    int j = ix - 1;
    for (int i = iy - 1; i >= 0; i--)
    // top left diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy - 1; i >= 0; i--)
    // top right diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    j = ix - 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom left diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom right diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    return 0;
}
int BB(int ix, int iy, int fx, int fy) // Black bishop
{
    int j = ix - 1;
    for (int i = iy - 1; i >= 0; i--)
    // top left diagnol
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy - 1; i >= 0; i--)
    // top right diagnol
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    j = ix - 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom left diagnol
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom right diagnol
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    return 0;
}
int WQ(int ix, int iy, int fx, int fy) // White Queen
{
    for (int i = ix - 1; i >= 0; i--)
    // left
    {
        if (board[iy][i] >= 0 && (fx == i && fy == iy))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy - 1; i >= 0; i--)
    // up
    {
        if (board[i][ix] >= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    for (int i = ix + 1; i <= 7; i++)
    // right
    {
        if (board[iy][i] >= 0 && (fy == iy && fx == i))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy + 1; i <= 7; i++)
    // down
    {
        if (board[i][ix] >= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    int j = ix - 1;
    for (int i = iy - 1; i >= 0; i--)
    // top left diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy - 1; i >= 0; i--)
    // top right diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    j = ix - 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom left diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom right diagnol
    {
        if (board[i][j] >= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    return 0;
}
int BQ(int ix, int iy, int fx, int fy) // Black Queen
{
    for (int i = ix - 1; i >= 0; i--)
    // left
    {
        if (board[iy][i] <= 0 && (fx == i && fy == iy))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy - 1; i >= 0; i--)
    // up
    {
        if (board[i][ix] <= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    for (int i = ix + 1; i <= 7; i++)
    // right
    {
        if (board[iy][i] <= 0 && (fy == iy && fx == i))
        {
            return 1;
        }
        else if (board[iy][i] != 0)
        {
            break;
        }
    }
    for (int i = iy + 1; i <= 7; i++)
    // down
    {
        if (board[i][ix] <= 0 && (fy == i && fx == ix))
        {
            return 1;
        }
        else if (board[i][ix] != 0)
        {
            break;
        }
    }
    int j = ix - 1;
    for (int i = iy - 1; i >= 0; i--)
    // top left
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy - 1; i >= 0; i--)
    // top right
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    j = ix - 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom left
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j--;
    }
    j = ix + 1;
    for (int i = iy + 1; i <= 7; i++)
    // bottom right
    {
        if (board[i][j] <= 0 && (fy == i && fx == j))
        {
            return 1;
        }
        else if (board[i][j] != 0)
        {
            break;
        }
        j++;
    }
    return 0;
}
int WK(int ix, int iy, int fx, int fy) // White Knight
{
    if (iy - 2 >= 0 && ix - 1 >= 0 && fy == iy - 2 && fx == ix - 1 &&
        board[fy][fx] >= 0)
    // up left
    {
        return 1;
    }
    if (iy - 2 >= 0 && ix + 1 < Length && fy == iy - 2 && fx == ix + 1 &&
        board[fy][fx] >= 0)
    // up right
    {
        return 1;
    }
    if (iy - 1 >= 0 && ix + 2 < Length && fy == iy - 1 && fx == ix + 2 &&
        board[fy][fx] >= 0)
    // right up
    {
        return 1;
    }
    if (iy + 1 >= 0 && ix + 2 < Length && fy == iy + 1 && fx == ix + 2 &&
        board[fy][fx] >= 0)
    // right down
    {
        return 1;
    }
    if (iy + 2 < Length && ix + 1 < Length && fy == iy + 2 && fx == ix + 1 &&
        board[fy][fx] >= 0)
    // down right
    {
        return 1;
    }
    if (iy + 2 < Length && ix - 1 >= 0 && fy == iy + 2 && fx == ix - 1 &&
        board[fy][fx] >= 0)
    // down left
    {
        return 1;
    }
    if (iy + 1 < Length && ix - 2 >= 0 && fy == iy + 1 && fx == ix - 2 &&
        board[fy][fx] >= 0)
    // left down
    {
        return 1;
    }
    if (iy - 1 >= 0 && ix - 2 >= 0 && fy == iy - 1 && fx == ix - 2 &&
        board[fy][fx] >= 0)
    // left up
    {
        return 1;
    }
    return 0;
}
int BK(int ix, int iy, int fx, int fy) // Black Knight
{
    if (iy - 2 >= 0 && ix - 1 >= 0 && fy == iy - 2 && fx == ix - 1 &&
        board[fy][fx] <= 0)
    // up left
    {
        return 1;
    }
    if (iy - 2 >= 0 && ix + 1 < Length && fy == iy - 2 && fx == ix + 1 &&
        board[fy][fx] <= 0)
    // up right
    {
        return 1;
    }
    if (iy - 1 >= 0 && ix + 2 < Length && fy == iy - 1 && fx == ix + 2 &&
        board[fy][fx] <= 0)
    // right up
    {
        return 1;
    }
    if (iy + 1 >= 0 && ix + 2 < Length && fy == iy + 1 && fx == ix + 2 &&
        board[fy][fx] <= 0)
    // right down
    {
        return 1;
    }
    if (iy + 2 < Length && ix + 1 < Length && fy == iy + 2 && fx == ix + 1 &&
        board[fy][fx] <= 0)
    // down right
    {
        return 1;
    }
    if (iy + 2 < Length && ix - 1 >= 0 && fy == iy + 2 && fx == ix - 1 &&
        board[fy][fx] <= 0)
    // down left
    {
        return 1;
    }
    if (iy + 1 < Length && ix - 2 >= 0 && fy == iy + 1 && fx == ix - 2 &&
        board[fy][fx] <= 0)
    // left down
    {
        return 1;
    }
    if (iy - 1 >= 0 && ix - 2 >= 0 && fy == iy - 1 && fx == ix - 2 &&
        board[fy][fx] <= 0)
    // left up
    {
        return 1;
    }
    return 0;
}
int WKICheck(int ix, int iy, int fx, int fy) // Check Detection for White
{
    if (ix - 1 >= 0 && iy - 1 >= 0 && fy == iy - 1 && fx == ix - 1 &&
        board[fy][fx] >= 0)
    // top left
    {
        return 1;
    }
    if (iy - 1 >= 0 && fx == ix && fy == iy - 1 && board[fy][fx] >= 0)
    // up
    {
        return 1;
    }
    if (iy - 1 >= 0 && ix + 1 < Length && fx == ix + 1 && fy == iy - 1 &&
        board[fy][fx] >= 0)
    // top right
    {
        return 1;
    }
    if (ix + 1 < Length && fy == iy && fx == ix + 1 && board[fy][fx] >= 0)
    // right
    {
        return 1;
    }
    if (ix + 1 < Length && iy + 1 < Length && fy == iy + 1 && fx == ix + 1 &&
        board[fy][fx] >= 0)
    // bottom right
    {
        return 1;
    }
    if (iy + 1 < Length && fy == iy + 1 && fx == ix && board[fy][fx] >= 0)
    // bottom
    {
        return 1;
    }
    if (ix - 1 >= 0 && iy + 1 < Length && fx == ix - 1 && fy == iy + 1 &&
        board[fy][fx] >= 0)
    // bottom left
    {
        return 1;
    }
    if (ix - 1 >= 0 && fy == iy && fx == ix - 1 && board[fy][fx] >= 0)
    // left
    {
        return 1;
    }
    return 0;
}
int WValid(int x, int y) // White Valid moves
{
    int ok = 0;
    for (int i = 0; i < Length; i++)
    // white valid moves
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] < 0)
            {
                if (board[i][j] == WPawn)
                {
                    // White Pawn can only attack diagonally
                    if ((i - 1 == y && j + 1 == x) ||
                        (i - 1 == y && j - 1 == x))
                    {
                        return 0; // Square is attacked
                    }
                }
                else
                {
                    ok = 0;
                }
                if (board[i][j] == WRook)
                {
                    ok = WR(j, i, x, y);
                }
                if (board[i][j] == WKnight)
                {
                    ok = WK(j, i, x, y);
                }
                if (board[i][j] == WBishop)
                {
                    ok = WB(j, i, x, y);
                }
                if (board[i][j] == WQueen)
                {
                    ok = WQ(j, i, x, y);
                }
                if (board[i][j] == WKing)
                {
                    ok = WKICheck(j, i, x, y);
                }
                if (ok == 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int BKI(int ix, int iy, int fx, int fy) // Black King
{
    if (ix - 1 >= 0 && iy - 1 >= 0 && fy == iy - 1 && fx == ix - 1 &&
        board[fy][fx] <= 0)
    // top left
    {
        if (WValid(ix - 1, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (iy - 1 >= 0 && fx == ix && fy == iy - 1 && board[fy][fx] <= 0)
    // up
    {
        if (WValid(ix, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (iy - 1 >= 0 && ix + 1 < Length && fx == ix + 1 && fy == iy - 1 &&
        board[fy][fx] <= 0)
    // top right
    {
        if (WValid(ix + 1, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (ix + 1 < Length && fy == iy && fx == ix + 1 && board[fy][fx] <= 0)
    // right
    {
        if (WValid(ix + 1, iy) == 1)
        {
            return 1;
        }
    }
    if (ix + 1 < Length && iy + 1 < Length && fy == iy + 1 && fx == ix + 1 &&
        board[fy][fx] <= 0)
    // bottom right
    {
        if (WValid(ix + 1, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (iy + 1 < Length && fy == iy + 1 && fx == ix && board[fy][fx] <= 0)
    // bottom
    {
        if (WValid(ix, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (ix - 1 >= 0 && iy + 1 < Length && fx == ix - 1 && fy == iy + 1 &&
        board[fy][fx] <= 0)
    // bottom left
    {
        if (WValid(ix - 1, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (ix - 1 >= 0 && fy == iy && fx == ix - 1 && board[fy][fx] <= 0)
    // left
    {
        if (WValid(ix - 1, iy) == 1)
        {
            return 1;
        }
    }
    if (rightBR == 0 && KingB == 0 && board[0][5] == 0 && board[0][6] == 0 &&
        fy == 0 && fx == 6)
    // kingside castle
    {
        if (WValid(4, 0) == 1)
        {
            if (WValid(5, 0) == 1)
            {
                if (WValid(6, 0) == 1)
                {
                    KingB = 1;
                    rightBR = 1;
                    board[0][7] = 0;
                    board[0][5] = BRook;
                    return 1;
                }
            }
        }
    }
    if (leftBR == 0 && KingB == 0 && board[0][3] == 0 && board[0][2] == 0 &&
        board[0][1] == 0 && fy == 0 && fx == 2)
    // queenside castle
    {
        if (WValid(4, 0) == 1)
        {
            if (WValid(3, 0) == 1)
            {
                if (WValid(2, 0) == 1)
                {
                    if (WValid(1, 0) == 1)
                    {
                        KingB = 1;
                        leftBR = 1;
                        board[0][0] = 0;
                        board[0][3] = BRook;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
int BValid(int x, int y) // Black Valid moves
{
    int ok = 0;
    for (int i = 0; i < Length; i++)
    // Black Valid moves
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] > 0)
            {
                if (board[i][j] == BPawn)
                {
                    // Black Pawn can only attack diagonally
                    if ((i + 1 == y && j + 1 == x) ||
                        (i + 1 == y && j - 1 == x))
                    {
                        return 0; // Square is attacked
                    }
                }
                else
                {
                    ok = 0;
                }
                if (board[i][j] == BRook)
                {
                    ok = BR(j, i, x, y);
                }
                if (board[i][j] == BKnight)
                {
                    ok = BK(j, i, x, y);
                }
                if (board[i][j] == BBishop)
                {
                    ok = BB(j, i, x, y);
                }
                if (board[i][j] == BQueen)
                {
                    ok = BQ(j, i, x, y);
                }
                if (board[i][j] == BKing)
                {
                    ok = BKI(j, i, x, y);
                }
                if (ok == 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
int WKI(int ix, int iy, int fx, int fy) // White King
{
    if (ix - 1 >= 0 && iy - 1 >= 0 && fy == iy - 1 && fx == ix - 1 &&
        board[fy][fx] >= 0)
    // top left
    {
        if (BValid(ix - 1, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (iy - 1 >= 0 && fx == ix && fy == iy - 1 && board[fy][fx] >= 0)
    // up
    {
        if (BValid(ix, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (iy - 1 >= 0 && ix + 1 < Length && fx == ix + 1 && fy == iy - 1 &&
        board[fy][fx] >= 0)
    // top right
    {
        if (BValid(ix + 1, iy - 1) == 1)
        {
            return 1;
        }
    }
    if (ix + 1 < Length && fy == iy && fx == ix + 1 && board[fy][fx] >= 0)
    // right
    {
        if (BValid(ix + 1, iy) == 1)
        {
            return 1;
        }
    }
    if (ix + 1 < Length && iy + 1 < Length && fy == iy + 1 && fx == ix + 1 &&
        board[fy][fx] >= 0)
    // bottom right
    {
        if (BValid(ix + 1, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (iy + 1 < Length && fy == iy + 1 && fx == ix && board[fy][fx] >= 0)
    // bottom
    {
        if (BValid(ix, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (ix - 1 >= 0 && iy + 1 < Length && fx == ix - 1 && fy == iy + 1 &&
        board[fy][fx] >= 0)
    // bottom left
    {
        if (BValid(ix - 1, iy + 1) == 1)
        {
            return 1;
        }
    }
    if (ix - 1 >= 0 && fy == iy && fx == ix - 1 && board[fy][fx] >= 0)
    // left
    {
        if (BValid(ix - 1, iy) == 1)
        {
            return 1;
        }
    }
    if (KingW == 0 && rightWR == 0 && board[7][5] == 0 && board[7][6] == 0 &&
        fy == 7 && fx == 6)
    // kingside castle
    {
        if (BValid(4, 7) == 1)
        {
            if (BValid(5, 7) == 1)
            {
                if (BValid(6, 7) == 1)
                {
                    board[7][7] = 0;
                    board[7][5] = WRook;
                    KingW = 1;
                    rightWR = 1;
                    return 1;
                }
            }
        }
    }
    if (KingW == 0 && rightWR == 0 && board[7][3] == 0 && board[7][2] == 0 &&
        board[7][1] == 0 && fy == 7 && fx == 2)
    // queenside castle
    {
        if (BValid(4, 7) == 1)
        {
            if (BValid(3, 7) == 1)
            {
                if (BValid(2, 7) == 1)
                {
                    if (BValid(1, 7) == 1)
                    {
                        board[7][0] = 0;
                        board[7][3] = WRook;
                        KingW = 1;
                        leftWR = 1;
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}
int WValid1(int x, int y) // White Valid moves
{
    int ok = 0;
    for (int i = 0; i < Length; i++)
    // white valid moves
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] < 0)
            {
                if (board[i][j] == WPawn)
                {
                    // White Pawn can only attack diagonally
                    if ((i - 1 == y && j + 1 == x) ||
                        (i - 1 == y && j - 1 == x))
                    {
                        return 0; // Square is attacked
                    }
                }
                else
                {
                    ok = 0;
                }
                if (board[i][j] == WRook)
                {
                    ok = WR(j, i, x, y);
                }
                if (board[i][j] == WKnight)
                {
                    ok = WK(j, i, x, y);
                }
                if (board[i][j] == WBishop)
                {
                    ok = WB(j, i, x, y);
                }
                if (board[i][j] == WQueen)
                {
                    ok = WQ(j, i, x, y);
                }
                if (board[i][j] == WKing)
                {
                    ok = WKI(j, i, x, y);
                }

                if (ok == 1)
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
void PositionWK() // Position of White King
{
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] == WKing)
            {
                KingWhite.x = j;
                KingWhite.y = i;
                break;
            }
        }
    }
}
void PositionBK() // Position of Black King
{
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] == BKing)
            {
                KingBlack.y = i;
                KingBlack.x = j;
                break;
            }
        }
    }
}
bool hasWhiteMoves() // White any valid moves
{
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] < 0)
            {
                for (int m = 0; m < Length; m++)
                {
                    for (int n = 0; n < Length; n++)
                    {
                        int ok = 0;
                        switch (board[i][j])
                        {
                        case WPawn:
                            ok = WP(j, i, n, m);
                            break;
                        case WRook:
                            ok = WR(j, i, n, m);
                            break;
                        case WKnight:
                            ok = WK(j, i, n, m);
                            break;
                        case WBishop:
                            ok = WB(j, i, n, m);
                            break;
                        case WQueen:
                            ok = WQ(j, i, n, m);
                            break;
                        case WKing:
                            ok = WKI(j, i, n, m);
                            break;
                        }
                        if (ok == 1)
                        {
                            int capturedPiece = board[m][n];
                            board[m][n] = board[i][j];
                            board[i][j] = 0;
                            PositionWK();
                            bool inCheck =
                                (BValid(KingWhite.x, KingWhite.y) == 0);
                            // Revert the move
                            board[i][j] = board[m][n];
                            board[m][n] = capturedPiece;
                            if (!inCheck)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
bool hasBlackMoves() // Black any valid moves
{
    for (int i = 0; i < Length; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            if (board[i][j] > 0)
            {
                for (int m = 0; m < Length; m++)
                {
                    for (int n = 0; n < Length; n++)
                    {
                        int ok = 0;
                        switch (board[i][j])
                        {
                        case BPawn:
                            ok = BP(j, i, n, m);
                            break;
                        case BRook:
                            ok = BR(j, i, n, m);
                            break;
                        case BKnight:
                            ok = BK(j, i, n, m);
                            break;
                        case BBishop:
                            ok = BB(j, i, n, m);
                            break;
                        case BQueen:
                            ok = BQ(j, i, n, m);
                            break;
                        case BKing:
                            ok = BKI(j, i, n, m);
                            break;
                        }
                        if (ok == 1)
                        {
                            int capturedPiece = board[m][n];
                            board[m][n] = board[i][j];
                            board[i][j] = 0;
                            PositionBK();
                            bool inCheck =
                                (WValid1(KingBlack.x, KingBlack.y) == 0);
                            // Revert the move
                            board[i][j] = board[m][n];
                            board[m][n] = capturedPiece;
                            if (!inCheck)
                            {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}
void resetGameState()
{

    size = 100;
    move = rightWR = leftWR = KingW = rightBR = leftBR = KingB = isMoving =
        WCheck = BCheck = Wpromotion = Bpromotion = Turn = WFlag = BFlag = dx =
            dy = NoMovedPiece = count4 = count1 = count2 = count3 = 0;
    enPassantB = enPassantW = -1;
    BenPassant = WenPassant = Break = checkmate = stalemate = menu = Bplace =
        Wplace = Reset = false;
    draw = Bdraw = Ldraw = Rdraw = Tdraw = true;
    int initialState[8][8] = {
        2,  3,  4,  5,  6,  4,  3,  2,  1,  1,  1,  1,  1,  1,  1,  1,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
        -1, -1, -1, -1, -1, -1, -1, -1, -2, -3, -4, -5, -6, -4, -3, -2,
    };

    // Clear all repetition board states:
    for (int i = 0; i < Length; ++i)
    {
        for (int j = 0; j < Length; ++j)
        {
            board[i][j] = Tempboard[i][j] = BTempboard[i][j] =
                LTempboard[i][j] = RTempboard[i][j] = TTempBoard[i][j] =
                    initialState[i][j];
            FBoard[i][j] = BFBoard[i][j] = LFBoard[i][j] = RFBoard[i][j] =
                TFBoard[i][j] = 100;
            Simboard[i][j] = BSimboard[i][j] = LSimboard[i][j] =
                RSimboard[i][j] = TSimBoard[i][j] = -100;
        }
    }
}
int main()
{
    RenderWindow window(VideoMode(800, 800), "Chess");
    // Sfml Window
    Texture t1, t2, t3, t4, t5, t6, t7, t8, t9, t10, t11, t12, t13, t14, t15,
        t16, t17, t18, t19, t20, t21;
    t1.loadFromFile("board.png");
    t2.loadFromFile("BP.png");
    t3.loadFromFile("WP.png");
    t4.loadFromFile("BR.png");
    t5.loadFromFile("WR.png");
    t6.loadFromFile("WK.png");
    t7.loadFromFile("BK.png");
    t8.loadFromFile("BB.png");
    t9.loadFromFile("WB.png");
    t10.loadFromFile("WQ.png");
    t11.loadFromFile("BQ.png");
    t12.loadFromFile("BKI.png");
    t13.loadFromFile("WKI.png");
    t14.loadFromFile("PromotionWhite.png");
    t15.loadFromFile("PromotionBlack.png");
    t16.loadFromFile("Stalemate.png");
    t17.loadFromFile("Menu.png");
    t18.loadFromFile("Button.png");
    t19.loadFromFile("Draw.png");
    t20.loadFromFile("Checkmate.png");
    t21.loadFromFile("Return.png");
    Sprite table(t1);
    Sprite BlackPawn(t2);
    Sprite WhitePawn(t3);
    Sprite BlackRook(t4);
    Sprite WhiteRook(t5);
    Sprite WhiteKnight(t6);
    Sprite BlackKnight(t7);
    Sprite BlackBishop(t8);
    Sprite WhiteBishop(t9);
    Sprite WhiteQueen(t10);
    Sprite BlackQueen(t11);
    Sprite BlackKing(t12);
    Sprite WhiteKing(t13);
    Sprite Moving;
    Sprite PromotionWhite(t14);
    Sprite PromotionBlack(t15);
    Sprite Stalemate(t16);
    Sprite Menu(t17);
    Sprite Button(t18);
    Sprite Draw(t19);
    Sprite Checkmate(t20);
    Sprite Return(t21);
    while (window.isOpen())
    // mouse position
    {
        FloatRect bounds = Button.getGlobalBounds();
        FloatRect boundary = Return.getGlobalBounds();
        Vector2i pos = Mouse::getPosition(window);
        x = pos.x / size;
        y = pos.y / size;
        Event e;
        Return.setPosition(0.0f, 700.0f);
        while (window.pollEvent(e))
        {
            if (e.type == Event::Resized)
            // Resizing window
            {
                FloatRect visibleArea(0, 0, e.size.width, e.size.height);
                window.setView(View(visibleArea));
            }
            if (e.type == Event::Closed)
            {
                window.close();
            }
            window.clear();
            if (e.type == Event::MouseButtonPressed)
            // M1
            {
                if (e.key.code == Mouse::Left)
                {
                    if (bounds.contains(pos.x, pos.y))
                    {
                        menu = true;
                    }
                    if (buttonVisible == true)
                    {
                        if (boundary.contains(pos.x, pos.y))
                        {
                            menu = false;
                            checkmate = false;
                            stalemate = false;
                            Break = false;
                            Reset = true;
                        }
                    }
                    if (Wpromotion == 1)
                    // White promotion
                    {
                        if (pos.y >= promotionW.y * size &&
                            pos.y <= (promotionW.y + 1) * size &&
                            pos.x >= promotionW.x * size &&
                            pos.x <= (promotionW.x + 1) * size)
                        {
                            if (pos.x % 100 < 50 && pos.y % 100 < 50 &&
                                pos.x % 100 > 0 && pos.y % 100 > 0)
                            {
                                board[promotionW.y][promotionW.x] = WRook;
                                Wpromotion = 0;
                            }
                            if (pos.x % 100 > 50 && pos.x % 100 < 100 &&
                                pos.y % 100 < 50 && pos.y % 100 > 0)
                            {
                                board[promotionW.y][promotionW.x] = WQueen;
                                Wpromotion = 0;
                            }
                            if (pos.x % 100 > 50 && pos.x % 100 < 100 &&
                                pos.y % 100 > 50 && pos.y % 100 < 100)
                            {
                                board[promotionW.y][promotionW.x] = WKnight;
                                Wpromotion = 0;
                            }
                            if (pos.x % 100 < 50 && pos.x % 100 > 0 &&
                                pos.y % 100 > 50 && pos.y % 100 < 100)
                            {
                                board[promotionW.y][promotionW.x] = WBishop;
                                Wpromotion = 0;
                            }
                            if (Wpromotion == 0)
                            {
                                PositionBK();
                                if (WValid1(KingBlack.x, KingBlack.y) == 0)
                                {
                                    BCheck = 1;
                                }
                            }
                        }
                    }
                    if (Bpromotion == 1)
                    // Black Promotion
                    {
                        if (pos.y >= promotionB.y * size &&
                            pos.y <= (promotionB.y + 1) * size &&
                            pos.x >= promotionB.x * size &&
                            pos.x <= (promotionB.x + 1) * size)
                        {
                            if (pos.x % 100 < 50 && pos.y % 100 < 50 &&
                                pos.x % 100 > 0 && pos.y % 100 > 0)
                            {
                                board[promotionB.y][promotionB.x] = BRook;
                                Bpromotion = 0;
                            }
                            if (pos.x % 100 > 50 && pos.x % 100 < 100 &&
                                pos.y % 100 < 50 && pos.y % 100 > 0)
                            {
                                board[promotionB.y][promotionB.x] = BQueen;
                                Bpromotion = 0;
                            }
                            if (pos.x % 100 > 50 && pos.x % 100 < 100 &&
                                pos.y % 100 > 50 && pos.y % 100 < 100)
                            {
                                board[promotionB.y][promotionB.x] = BKnight;
                                Bpromotion = 0;
                            }
                            if (pos.x % 100 < 50 && pos.x % 100 > 0 &&
                                pos.y % 100 > 50 && pos.y % 100 < 100)
                            {
                                board[promotionB.y][promotionB.x] = BBishop;
                                Bpromotion = 0;
                            }
                            if (Bpromotion == 0)
                            {
                                PositionWK();
                                if (BValid(KingWhite.x, KingWhite.y) == 0)
                                {
                                    WCheck = 1;
                                }
                            }
                        }
                    }
                    if (board[y][x] != 0)
                    // piece selection
                    {
                        dx = pos.x - x * 100;
                        dy = pos.y - y * 100;
                        if (board[y][x] == BPawn && isMoving == 1)
                        {
                            NoMovedPiece = BPawn;
                            Moving = BlackPawn;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WPawn && isMoving == 0)
                        {
                            NoMovedPiece = WPawn;
                            Moving = WhitePawn;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == BRook && isMoving == 1)
                        {
                            NoMovedPiece = BRook;
                            Moving = BlackRook;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WRook && isMoving == 0)
                        {
                            NoMovedPiece = WRook;
                            Moving = WhiteRook;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WKnight && isMoving == 0)
                        {
                            NoMovedPiece = WKnight;
                            Moving = WhiteKnight;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == BKnight && isMoving == 1)
                        {
                            NoMovedPiece = BKnight;
                            Moving = BlackKnight;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == BBishop && isMoving == 1)
                        {
                            NoMovedPiece = BBishop;
                            Moving = BlackBishop;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WBishop && isMoving == 0)
                        {
                            NoMovedPiece = WBishop;
                            Moving = WhiteBishop;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WQueen && isMoving == 0)
                        {
                            NoMovedPiece = WQueen;
                            Moving = WhiteQueen;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == BQueen && isMoving == 1)
                        {
                            NoMovedPiece = BQueen;
                            Moving = BlackQueen;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == BKing && isMoving == 1)
                        {
                            NoMovedPiece = BKing;
                            Moving = BlackKing;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == WKing && isMoving == 0)
                        {
                            NoMovedPiece = WKing;
                            Moving = WhiteKing;
                            board[y][x] = 0;
                        }
                        if (board[y][x] == 0)
                        {
                            move = 1;
                            Initial.x = x;
                            Initial.y = y;
                        }
                    }
                }
            }
            if (e.type == Event::MouseButtonReleased)
            // execute moves
            {
                if (e.key.code == Mouse::Left)
                {
                    int ok = 2;
                    if (NoMovedPiece == WPawn && move == 1)
                    {
                        ok = WP(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == BPawn && move == 1)
                    {
                        ok = BP(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == WRook && move == 1)
                    {
                        ok = WR(Initial.x, Initial.y, x, y);
                        if (ok == 1 && leftWR == 0 && Initial.y == 7 &&
                            Initial.x == 0)
                        {
                            leftWR = 1;
                        }
                        if (ok == 1 && rightWR == 0 && Initial.y == 7 &&
                            Initial.x == 7)
                        {
                            rightWR = 1;
                        }
                    }
                    if (NoMovedPiece == BRook && move == 1)
                    {
                        ok = BR(Initial.x, Initial.y, x, y);
                        if (ok == 1 && rightBR == 0 && Initial.y == 0 &&
                            Initial.x == 7)
                        {
                            rightBR = 1;
                        }
                        if (ok == 1 && leftBR == 0 && Initial.y == 0 &&
                            Initial.x == 0)
                        {
                            leftBR = 1;
                        }
                    }
                    if (NoMovedPiece == WBishop && move == 1)
                    {
                        ok = WB(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == BBishop && move == 1)
                    {
                        ok = BB(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == WQueen && move == 1)
                    {
                        ok = WQ(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == BQueen && move == 1)
                    {
                        ok = BQ(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == WKnight && move == 1)
                    {
                        ok = WK(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == BKnight && move == 1)
                    {
                        ok = BK(Initial.x, Initial.y, x, y);
                    }
                    if (NoMovedPiece == BKing && move == 1)
                    {
                        ok = BKI(Initial.x, Initial.y, x, y);
                        if (ok == 1 && KingB == 0)
                        {
                            KingB = 1;
                        }
                    }
                    if (NoMovedPiece == WKing && move == 1)
                    {
                        ok = WKI(Initial.x, Initial.y, x, y);
                        if (ok == 1 && KingW == 0)
                        {
                            KingW = 1;
                        }
                    }
                    if (ok == 1)
                    {
                        int nr = board[y][x];
                        board[y][x] = NoMovedPiece;
                        if (y == 0 && NoMovedPiece == WPawn)
                        {
                            Wpromotion = 1;
                            promotionW.x = x;
                            promotionW.y = y;
                            board[y][x] = 0;
                        }
                        if (y == 7 && NoMovedPiece == BPawn)
                        {
                            Bpromotion = 1;
                            promotionB.x = x;
                            promotionB.y = y;
                            board[y][x] = 0;
                        }
                        if (isMoving == 0)
                        {
                            if (WCheck == 1)
                            {
                                PositionWK();
                                if (BValid(KingWhite.x, KingWhite.y) == 0)
                                {
                                    board[Initial.y][Initial.x] = NoMovedPiece;
                                    board[y][x] = nr;
                                }
                                else
                                {
                                    WCheck = 0;
                                    PositionBK();
                                    if (WValid1(KingBlack.x, KingBlack.y) == 0)
                                    {
                                        BCheck = 1;
                                    }
                                    isMoving = 1;
                                }
                            }
                            else
                            {
                                PositionWK();
                                if (BValid(KingWhite.x, KingWhite.y) == 0)
                                {
                                    board[Initial.y][Initial.x] = NoMovedPiece;
                                    board[y][x] = nr;
                                }
                                else
                                {
                                    PositionBK();
                                    if (WValid1(KingBlack.x, KingBlack.y) == 0)
                                    {
                                        BCheck = 1;
                                    }
                                    isMoving = 1;
                                }
                            }
                        }
                        else
                        {
                            if (BCheck == 1)
                            {
                                PositionBK();
                                if (WValid1(KingBlack.x, KingBlack.y) == 0)
                                {
                                    board[Initial.y][Initial.x] = NoMovedPiece;
                                    board[y][x] = nr;
                                }
                                else
                                {
                                    BCheck = 0;
                                    PositionWK();
                                    if (BValid(KingWhite.x, KingWhite.y) == 0)
                                    {
                                        WCheck = 1;
                                    }
                                    isMoving = 0;
                                }
                            }
                            else
                            {
                                PositionBK();
                                if (WValid1(KingBlack.x, KingBlack.y) == 0)
                                {
                                    board[Initial.y][Initial.x] = NoMovedPiece;
                                    board[y][x] = nr;
                                }
                                else
                                {
                                    PositionWK();
                                    if (BValid(KingWhite.x, KingWhite.y) == 0)
                                    {
                                        WCheck = 1;
                                    }
                                    isMoving = 0;
                                }
                            }
                        }
                        if (Turn == 3)
                        {
                            for (int i = 0; i <= 7; ++i)
                            {
                                for (int j = 0; j <= 7; ++j)
                                {
                                    TFBoard[i][j] = board[i][j];
                                }
                            }
                        }
                        else if (Turn == 7)
                        {
                            for (int i = 0; i <= 7; ++i)
                            {
                                for (int j = 0; j <= 7; ++j)
                                {
                                    TSimBoard[i][j] = board[i][j];
                                }
                            }
                        }
                        Turn += 1;
                        // draw by threefold repetition
                        draw = Bdraw = Ldraw = Rdraw = Tdraw = true;
                        if ((Turn - 1) % 4 == 0)
                        {
                            count4 += Turn - 1;
                            if ((count4 / 4) % 3 == 0)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        Simboard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count4 / 4) % 3 == 1)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        FBoard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count4 / 4) % 3 == 2)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        Tempboard[i][j] = board[i][j];
                                    }
                                }
                            }
                        }
                        else if ((Turn - 2) % 4 == 0)
                        {
                            count1 += Turn - 2;
                            if ((count1 / 4) % 3 == 0)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        BSimboard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count1 / 4) % 3 == 1)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        BFBoard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count1 / 4) % 3 == 2)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        BTempboard[i][j] = board[i][j];
                                    }
                                }
                            }
                        }
                        else if ((Turn - 3) % 4 == 0)
                        {
                            count2 += Turn - 3;
                            if ((count2 / 4) % 3 == 0)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        LSimboard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count2 / 4) % 3 == 1)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        LFBoard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count2 / 4) % 3 == 2)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        LTempboard[i][j] = board[i][j];
                                    }
                                }
                            }
                        }
                        else if (Turn % 4 == 0)
                        {
                            count3 += Turn;
                            if ((count3 / 4) % 3 == 0)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        RSimboard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count3 / 4) % 3 == 1)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        RFBoard[i][j] = board[i][j];
                                    }
                                }
                            }
                            else if ((count3 / 4) % 3 == 2)
                            {
                                for (int i = 0; i <= 7; ++i)
                                {
                                    for (int j = 0; j <= 7; ++j)
                                    {
                                        RTempboard[i][j] = board[i][j];
                                    }
                                }
                            }
                        }
                        count4 = count3 = count2 = count1 = 0;
                        for (int i = 0; i < Length; i++)
                        {
                            for (int j = 0; j < Length; j++)
                            {
                                if (FBoard[i][j] != Simboard[i][j] ||
                                    FBoard[i][j] != Tempboard[i][j] ||
                                    Simboard[i][j] != Tempboard[i][j])
                                {
                                    draw = false;
                                }
                                if (BFBoard[i][j] != BSimboard[i][j] ||
                                    BFBoard[i][j] != BTempboard[i][j] ||
                                    BSimboard[i][j] != BTempboard[i][j])
                                {
                                    Bdraw = false;
                                }
                                if (LFBoard[i][j] != LSimboard[i][j] ||
                                    LFBoard[i][j] != LTempboard[i][j] ||
                                    LSimboard[i][j] != LTempboard[i][j])
                                {
                                    Ldraw = false;
                                }
                                if (RFBoard[i][j] != RSimboard[i][j] ||
                                    RFBoard[i][j] != RTempboard[i][j] ||
                                    RSimboard[i][j] != RTempboard[i][j])
                                {
                                    Rdraw = false;
                                }
                                if (TFBoard[i][j] != TSimBoard[i][j] ||
                                    TFBoard[i][j] != TTempBoard[i][j] ||
                                    TSimBoard[i][j] != TTempBoard[i][j])
                                {
                                    Tdraw = false;
                                }
                            }
                        }
                        if (draw == true || Bdraw == true || Ldraw == true ||
                            Rdraw == true || Tdraw == true)
                        {
                            Break = true;
                        }
                        if (((WCheck == 1) && hasWhiteMoves() == false) ||
                            ((BCheck == 1) && hasBlackMoves() == false))
                        {
                            checkmate = true;
                        }
                        else if (((WCheck != 1) && hasWhiteMoves() == false) ||
                                 ((BCheck != 1) && hasBlackMoves() == false))
                        {
                            stalemate = true;
                        }
                        if (WenPassant == true)
                        // En Passant Tracking
                        {
                            WFlag += 1;
                        }
                        if (BenPassant == true)
                        {
                            BFlag += 1;
                        }
                        if (WFlag >= 2)
                        {
                            WenPassant = false;
                            WFlag = 0;
                            enPassantW = -1;
                        }
                        else if (BFlag >= 2)
                        {
                            BenPassant = false;
                            enPassantB = -1;
                            BFlag = 0;
                        }
                    }
                    else if (ok == 0)
                    {
                        board[Initial.y][Initial.x] = NoMovedPiece;
                    }
                    move = 0;
                    // Reset Variables
                }
            }
        }
        window.clear();
        if (menu == false)
        {
            window.draw(Menu);
            window.draw(Button);

            buttonVisible = false;
        }
        else if (menu == true)
        {
            window.draw(table);
            if (Reset == true)
            {
                resetGameState();
            }
            Reset = false;
            if (Wpromotion == 1)
            // redraw board
            {
                PromotionWhite.setPosition(promotionW.x * size,
                                           promotionW.y * size);
                window.draw(PromotionWhite);
            }
            if (Bpromotion == 1)
            {
                PromotionBlack.setPosition(promotionB.x * size,
                                           promotionB.y * size);
                window.draw(PromotionBlack);
            }
            if (move == 1)
            {
                Moving.setPosition(pos.x - dx, pos.y - dy);
                window.draw(Moving);
            }
            for (int i = 0; i < Length; i++)
            {
                for (int j = 0; j < Length; j++)
                {
                    if (board[i][j] != 0)
                    {
                        if (board[i][j] == BPawn)
                        {
                            BlackPawn.setPosition(j * size, i * size);
                            window.draw(BlackPawn);
                        }
                        if (board[i][j] == WPawn)
                        {
                            WhitePawn.setPosition(j * size, i * size);
                            window.draw(WhitePawn);
                        }
                        if (board[i][j] == BRook)
                        {
                            BlackRook.setPosition(j * size, i * size);
                            window.draw(BlackRook);
                        }
                        if (board[i][j] == WRook)
                        {
                            WhiteRook.setPosition(j * size, i * size);
                            window.draw(WhiteRook);
                        }
                        if (board[i][j] == WKnight)
                        {
                            WhiteKnight.setPosition(j * size, i * size);
                            window.draw(WhiteKnight);
                        }
                        if (board[i][j] == BKnight)
                        {
                            BlackKnight.setPosition(j * size, i * size);
                            window.draw(BlackKnight);
                        }
                        if (board[i][j] == BBishop)
                        {
                            BlackBishop.setPosition(j * size, i * size);
                            window.draw(BlackBishop);
                        }
                        if (board[i][j] == WBishop)
                        {
                            WhiteBishop.setPosition(j * size, i * size);
                            window.draw(WhiteBishop);
                        }
                        if (board[i][j] == WQueen)
                        {
                            WhiteQueen.setPosition(j * size, i * size);
                            window.draw(WhiteQueen);
                        }
                        if (board[i][j] == BQueen)
                        {
                            BlackQueen.setPosition(j * size, i * size);
                            window.draw(BlackQueen);
                        }
                        if (board[i][j] == BKing)
                        {
                            BlackKing.setPosition(j * size, i * size);
                            window.draw(BlackKing);
                        }
                        if (board[i][j] == WKing)
                        {
                            WhiteKing.setPosition(j * size, i * size);
                            window.draw(WhiteKing);
                        }
                    }
                }
            }

            buttonVisible = false;
        }
        if (Break == true)
        {
            window.draw(Draw);
            window.draw(Return);
            buttonVisible = true;
        }

        if (checkmate == true)
        {
            window.draw(Checkmate);
            window.draw(Return);
            buttonVisible = true;
        }
        if (stalemate == true)
        {
            window.draw(Stalemate);
            window.draw(Return);
            buttonVisible = true;
        }

        window.display();
    }
    return 0;
}
