import java.util.Scanner;

import static java.lang.Integer.max;
import static java.lang.Integer.min;
import static java.lang.System.exit;

public class Jatek {
    private int k;
    private int jatekosTipusa;

    private int[] maxPlayerPos;
    private int[] minPlayerPos;

    private class Move
    {
        public int row, column, rowBlocked, columnBlocked;

        private Move()
        {
            row=0;
            column=0;
            rowBlocked=0;
            columnBlocked=0;
        }

        private Move(int row, int column, int rowBlocked, int columnBlocked)
        {
            this.row=row;
            this.column=column;
            this.rowBlocked=rowBlocked;
            this.columnBlocked=columnBlocked;
        }

        private void setBestMove(int row, int column, int rowBlocked, int columnBlocked)
        {
            this.row=row;
            this.column=column;
            this.rowBlocked=rowBlocked;
            this.columnBlocked=columnBlocked;
        }

    };

    private int[] getMoves(boolean board[][]) {
        System.out.println("Lepes:Add meg a sort vagy az oszlopot ahova lepnel");

        int[] points={0,0};
        Scanner input = new Scanner(System.in);


        while (board[points[0]][points[1]] == true) {

            points[0] = input.nextInt();
            points[1] = input.nextInt();

            if (board[points[0]][points[1]] == true) {
                System.out.println("Hibasan adtad meg az adatokat, probald ujra");
            }
        }

        return points;
    }

    private int[] getBlocks(boolean board[][]) {
        System.out.println("BLOKKOLAS:Blokkolj egy mezot!");

        int[] points={0,0};
        Scanner input = new Scanner(System.in);


        while (board[points[0]][points[1]] == true) {

            points[0] = input.nextInt();
            points[1] = input.nextInt();

            if (board[points[0]][points[1]] == true) {
                System.out.println("A cella mar foglalt");
            }
        }

        return points;
    }

    private boolean[][] initializeTable()
    {
        boolean [][] board=new boolean[k+2][k+2];
        board=setBoundsAroundTable(board);

        for(int i=1;i<=k;i++)
        {
            for(int j=1;j<=k;j++)
            {
                board[i][j]=false;
            }
        }

        maxPlayerPos[0] = k;
        maxPlayerPos[1] = (k / 2)+1;
        minPlayerPos[0] = 1;
        minPlayerPos[1] = (k / 2)+1;

        board[maxPlayerPos[0]][maxPlayerPos[1]]=true;
        board[minPlayerPos[0]][minPlayerPos[1]]=true;

        return board;
    }

    private boolean[][] setBoundsAroundTable(boolean[][] initialBoard)
    {
        boolean[][] board=initialBoard;

        for (int j = 0; j <= this.k+1; j++)
        {
            board[0][j] = true;
            board[k+1][j] = true;
        }

        for (int i = 0; i <= this.k+1; i++)
        {
            board[i][0] = true;
            board[i][k+1] = true;
        }
        return board;
    }

    public void printBoard(boolean[][] board)
    {
        for(int i=1;i<=k;i++)
        {
            for(int j=1;j<=k;j++)
            {
                boolean isPlayer=false;

                if((i== maxPlayerPos[0]) && (j== maxPlayerPos[1]))
                {
                    System.out.print("M ");
                    isPlayer=true;
                }
                if ((i == minPlayerPos[0]) && (j == minPlayerPos[1])) {
                    isPlayer=true;
                    System.out.print("N ");
                }
                if ((board[i][j]==true) && (isPlayer==false)) System.out.print("B ");
                if((board[i][j]==false) && (isPlayer==false)) System.out.print("o ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public Jatek(int k, int jatekosTipusa) {
        if (k % 2 == 0) {
            System.out.println("Hiba: A k paratlan kell legyen");
            exit(0);
        }

        if ((jatekosTipusa != 1) && (jatekosTipusa != 2)) {
            System.out.println("Ha jatekos kezdjen akkor 2-ot adj meg, ha az AI 1-et!");
            exit(0);
        } else {
            this.k = k;
            this.jatekosTipusa = jatekosTipusa;
            this.maxPlayerPos = new int[2];
            this.minPlayerPos = new int[2];
        }
    }


    public int terminalState(boolean[][] board, int x, int y, int isPlayer)
    {
        int[] checkX = {-1, -1, 0, 1, 1,  1,  0, -1};
        int[] checkY = { 0,  1, 1, 1, 0, -1, -1, -1};

        if(isPlayer==0) { //Ha AI
            for (int i = 0; i < 8; i++) {
                if (board[x + checkX[i]][y + checkY[i]] == false) {
                    return 0;
                }
            }

            return -1;
        }
        else //Ha Jatekos
        {
            for (int i = 0; i < 8; i++) {
                if (board[x + checkX[i]][y + checkY[i]] == false) {
                    return 0;
                }
            }
            return 1;
        }
    }

    public int getHeuristicValue(boolean[][] board, int alpha, int maxX, int maxY, int minX, int minY)
    {
        int freeMaxPlayerMoves = 0;
        int freeMinPlayerMoves = 0;

        int[] checkX = {-1, -1, 0, 1, 1, 1, 0, -1};
        int[] checkY = {0, 1, 1, 1, 0, -1, -1, -1};

        for (int i = 0; i < 8; i++) {
            if (board[maxX + checkX[i]][maxY + checkY[i]] == false) {
                ++freeMaxPlayerMoves;
            }

            if (board[minX + checkX[i]][minY + checkY[i]] == false) {
                ++freeMinPlayerMoves;
            }
        }
        return freeMaxPlayerMoves-(alpha*freeMinPlayerMoves);
    }

    public int minimaxEval(boolean[][] board, int depth, int alpha, int beta, int maxX, int maxY, int minX, int minY, int isMaximizing)
    {
        int[] checkX = {-1, -1, 0, 1, 1,  1,  0, -1};
        int[] checkY = { 0,  1, 1, 1, 0, -1, -1, -1};
        int score;

        if (isMaximizing==0)
        {
            if (depth == 3)
            {
                return getHeuristicValue(board,3,maxX, maxY, minX, minY);
            }

            score= terminalState(board, maxX, maxY, isMaximizing);

            if (score != 0)
            {
                return score;
            }

            boolean pruningBreak = false;

            int best = -Integer.MAX_VALUE;
            for (int l = 0; l < 8; l++)
            {
                int newPosX = maxX + checkX[l];
                int newPosY = maxY + checkY[l];

                if(board[newPosX][newPosY]==false)
                {
                    board[maxX][maxY] = false;
                    board[newPosX][newPosY] = true;

                    for (int i = 1; i <=k; i++)
                    {
                        for (int j = 1; j <= k; j++)
                        {
                            if (board[i][j] == false)
                            {
                                board[i][j] = true;
                                best = max(best, minimaxEval(board, depth+1,alpha, beta, newPosX, newPosY, minX, minY, 1));
                                alpha = max(alpha, best);
                                board[i][j] = false;

                                if (alpha >= beta)
                                {
                                    pruningBreak = true;
                                    break;
                                }
                            }
                        }
                        if (pruningBreak)
                        {
                            break;
                        }
                    }

                    board[maxX][maxY] = true;
                    board[newPosX][newPosY] = false;

                    if (pruningBreak)
                    {
                        break;
                    }
                }
            }

            return best;
        }
        else
        {
            if (depth == 3)
            {
                return getHeuristicValue(board,3,maxX, maxY, minX, minY);
            }

            score= terminalState(board, minX, minY, isMaximizing);

            if (score != 0)
            {
                return score;
            }

            boolean pruningBreak = false;

            int best = Integer.MAX_VALUE;
            for (int l = 0; l < 8; l++)
            {
                int newPosX = minX + checkX[l];
                int newPosY = minY + checkY[l];

                if(board[newPosX][newPosY]==false)
                {
                    board[minX][minY] = false;
                    board[newPosX][newPosY] = true;

                    for (int i = 1; i <= k; i++)
                    {
                        for (int j = 1; j <= k; j++)
                        {
                            if (board[i][j] == false)
                            {
                                board[i][j] = true;

                                best = min(best, minimaxEval(board, depth+1,alpha, beta, maxX, maxY, newPosX, newPosY, 0));
                                beta = min(best, beta);

                                board[i][j] = false;

                                if (alpha >= beta)
                                {
                                    pruningBreak = true;
                                    break;
                                }
                            }
                        }
                        if (pruningBreak)
                        {
                            break;
                        }
                    }

                    board[minX][minY] = true;
                    board[newPosX][newPosY] = false;

                    if (pruningBreak)
                    {
                        break;
                    }
                }
            }

            return best;
        }
    }

    public Move findBestMove(boolean[][] board, int maxX, int maxY, int minX, int minY)
    {
        int[] checkX = {-1, -1, 0, 1, 1,  1,  0, -1};
        int[] checkY = { 0,  1, 1, 1, 0, -1, -1, -1};

        Move bestMove=new Move();

        int bestVal = -Integer.MAX_VALUE;

        for (int l = 0; l < 8; l++)
        {
            int newPosX = maxX + checkX[l];
            int newPosY = maxY + checkY[l];

            if(board[newPosX][newPosY]==false)
            {
                board[maxX][maxY] = false;
                board[newPosX][newPosY] = true;

                for (int i = 1; i <= k; i++)
                {
                    for (int j = 1; j <= k; j++)
                    {
                        if (board[i][j] == false)
                        {
                            board[i][j] = true;

                            int moveVal = minimaxEval(board,0, -Integer.MAX_VALUE, Integer.MAX_VALUE, newPosX, newPosY, minX, minY, 1);

                            board[i][j] = false;

                            if (moveVal > bestVal)
                            {
                                bestMove.setBestMove(newPosX,newPosY,i,j);
                                bestVal = moveVal;
                            }
                        }
                    }
                }

                board[maxX][maxY] = true;
                board[newPosX][newPosY] = false;
            }
        }
        return bestMove;
    }

    public void startGame()
    {
        boolean board[][] = initializeTable();
        printBoard(board);

        int isPlayer = 0;

        if(jatekosTipusa==1)
        {
            isPlayer=1;
        }

        int x = k;
        int y = k;

        int matchWinner;

        do
        {
            if (isPlayer==0)
            {
                Move nextBestMove = new Move();
                nextBestMove = findBestMove(board, maxPlayerPos[0], maxPlayerPos[1], minPlayerPos[0], minPlayerPos[1]);
                board[maxPlayerPos[0]][maxPlayerPos[1]] = false;
                maxPlayerPos[0] = nextBestMove.row;
                maxPlayerPos[1] = nextBestMove.column;
                board[maxPlayerPos[0]][maxPlayerPos[1]] = true;
                board[nextBestMove.rowBlocked][nextBestMove.columnBlocked] = true;

                x = minPlayerPos[0];
                y = minPlayerPos[1];
                isPlayer=1;
            }
            else
            {
                int[] playerMove=new int[2];
                playerMove=getMoves(board);
                board[minPlayerPos[0]][minPlayerPos[1]] = false;
                minPlayerPos[0] = playerMove[0];
                minPlayerPos[1] = playerMove[1];

                board[playerMove[0]][playerMove[1]] = true;

                int [] blockCellMove=new int[2];
                blockCellMove=getBlocks(board);
                board[blockCellMove[0]][blockCellMove[1]] = true;

                x = maxPlayerPos[0];
                y = maxPlayerPos[1];
                isPlayer=0;
            }
            printBoard(board);

        } while ((matchWinner = terminalState(board, x, y, isPlayer)) == 0);


        if (matchWinner == -1)
        {
            System.out.println("Gratulalok nyertel!");
        }
        else
        {
            System.out.println("Sajnos nyert az AI :(");
        }
    }
}