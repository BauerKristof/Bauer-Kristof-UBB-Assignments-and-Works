import java.util.ArrayList;

public class TablaSzerkezet {
    private int             k;
    private int[]           maxPlayerPos;
    private int[]           minPlayerPos;
    private int             nodusErteke;
    ArrayList<TablaSzerkezet>    nodus;
    private TablaSzerkezet legjobbLepes;
    private int             jatekosTipusa;
    private boolean[][]     board;

    public TablaSzerkezet(int k, int jatekosTipusa) {

        this.k  = k;
        this.board = new boolean[k+2][k+2];
        this.jatekosTipusa = jatekosTipusa;
        this.nodusErteke = 0;
        this.maxPlayerPos = new int[2];
        this.minPlayerPos = new int[2];

        intializeTable();
        setBoundsAroundTable();

    }

    public TablaSzerkezet(TablaSzerkezet copyTabla) {
        this.k = copyTabla.k;
        this.board = new boolean[k+2][k+2];

        for(int i = 0; i <= k+1; i++) {
            for(int j = 0; j <= k+1; j++) {
                this.board[i][j] = copyTabla.board[i][j];
            }
        }


        this.jatekosTipusa = copyTabla.jatekosTipusa;
        this.nodusErteke = copyTabla.nodusErteke;

        this.maxPlayerPos = new int[2];
        this.minPlayerPos = new int[2];

        this.maxPlayerPos[0] = copyTabla.maxPlayerPos[0];
        this.maxPlayerPos[1] = copyTabla.maxPlayerPos[1];
        this.minPlayerPos[0] = copyTabla.minPlayerPos[0];
        this.minPlayerPos[1] = copyTabla.minPlayerPos[1];
    }

    private void intializeTable()
    {
        for (int i = 1; i <= k; i++)
        {
            for (int j = 1; j <= k; j++)
            {
                this.board[i][j]=false;
            }
        }


        this.maxPlayerPos[0] = k;
        this.maxPlayerPos[1] = (k / 2)+1;
        this.minPlayerPos[0] = 1;
        this.minPlayerPos[1] = (k / 2)+1;
    }

    private void setBoundsAroundTable()
    {
        for (int j = 0; j <= this.k+1; j++)
        {
            this.board[0][j] = true;
            this.board[k+1][j] = true;

        }

        for (int i = 0; i <= this.k+1; i++)
        {
            this.board[i][0] = true;
            this.board[i][k+1] = true;

        }
    }


    private boolean checkBoards(TablaSzerkezet tablaSz)
    {
        for(int i = 0; i <= k+1; i++) {
            for(int j = 0; j <= k+1; j++) {
                if(this.board[i][j] != tablaSz.board[i][j]) {
                    return false;
                }
            }
        }
        return true;
    }



    public boolean szabadHely(int i, int j) {
        if( (i== maxPlayerPos[0]) && (j== maxPlayerPos[1]))
        {
            return false;
        }

        if( (i== minPlayerPos[0]) && (j== minPlayerPos[1]))
        {
            return false;
        }

        if(board[i][j]==true)
        {
            return false;
        }

        return true;
    }


    public boolean terminalState() {
        int[] checkX = {-1, -1, 0, 1, 1,  1,  0, -1};
        int[] checkY = { 0,  1, 1, 1, 0, -1, -1, -1};


        if(jatekosTipusa == 1) {
            boolean megLephet;

            for(int i = 0; i < 8; i++) {
                    megLephet= szabadHely(maxPlayerPos[0] + checkX[i], maxPlayerPos[1] + checkY[i]);
                    if(megLephet) {
                        return false;
                    }
            }
        }
        else {
            boolean megLephet;

            for(int i = 0; i < 8; i++) {
                megLephet= szabadHely(minPlayerPos[0] + checkX[i], minPlayerPos[1] + checkY[i]);

                if(megLephet) {
                        return false;
                    }
            }
        }

        return true;
    }



    public int getJatekosTipusa() {
        return jatekosTipusa;
    }

    public void setJatekosTipusa(int jatekosTipusa) {
        this.jatekosTipusa = jatekosTipusa;
    }


    public void setMaxPlayer(int i, int j) {
        this.maxPlayerPos[0] = i;
        this.maxPlayerPos[1] = j;
    }

    public int[] getMaxPlayerPos() {
        return maxPlayerPos;
    }

    public void setMinPlayer(int i, int j) {
        this.minPlayerPos[0] = i;
        this.minPlayerPos[1] = j;
    }

    public int[] getMinPlayerPos() {
        return minPlayerPos;
    }


    public void setBoard(boolean[][] board) {
        this.board = board;
    }


    public boolean[][] getBoard() {
        return board;
    }

    public void setNodus(ArrayList<TablaSzerkezet> nodus) {
        this.nodus = nodus;
    }

    public ArrayList<TablaSzerkezet> getNodus() {
        return nodus;
    }

    public TablaSzerkezet getLegjobbLepes() {
        return legjobbLepes;
    }

    public void setLegjobbLepes(TablaSzerkezet legjobbLepes) {
        this.legjobbLepes = legjobbLepes;
    }


    public int getNodusErteke() {
        return nodusErteke;
    }

    public void setNodusErteke(int tablaErtek) {
        this.nodusErteke = tablaErtek;
    }

    public TablaSzerkezet setBounds(int i, int j) {
        board[i][j] = true;
        return this;
    }



    public boolean isEqual(TablaSzerkezet g) {
        if(this.maxPlayerPos[0] != g.maxPlayerPos[0] || this.maxPlayerPos[1] != g.maxPlayerPos[1]) {
            return false;
        }
        if(this.minPlayerPos[0] != g.minPlayerPos[0] || this.minPlayerPos[1] != g.minPlayerPos[1]) {
            return false;
        }

        boolean azonos=checkBoards(g);
        if(!azonos) return false;

        return true;
    }

    public void printBoard()
    {
        //  for (int i = 0; i <= k+1; i++)
        for(int i=1;i<=k;i++)
        {
            //   for (int j = 0; j <= k+1; j++)
            for(int j=1;j<=k;j++)
            {
                if((i== maxPlayerPos[0]) && (j== maxPlayerPos[1])) System.out.print("M ");
                else if ((i == minPlayerPos[0]) && (j == minPlayerPos[1])) System.out.print("N ");
                else if (board[i][j]==true) System.out.print("B ");
                else System.out.print("o ");
            }
            System.out.println();
        }
        System.out.println();
    }

    public ArrayList<TablaSzerkezet> szamolKovLepes() {

        this.nodus = new ArrayList<>();

        int[] checkX = {-1, -1, 0, 1, 1,  1,  0, -1};
        int[] checkY = { 0,  1, 1, 1, 0, -1, -1, -1};


        if(this.jatekosTipusa == 1) {

            for(int i = 0; i < 8; i++) {

                    if(szabadHely(maxPlayerPos[0] + checkX[i], maxPlayerPos[1] + checkY[i])) {
                        TablaSzerkezet ahovaLepett = new TablaSzerkezet(this);

                        ahovaLepett.setMaxPlayer(maxPlayerPos[0] + checkX[i], maxPlayerPos[1] + checkY[i]);

                        for(int row = 0; row <= k+1; row++) {
                            for(int column = 0; column <= k+1; column++) {

                                if(ahovaLepett.szabadHely(row, column)) {
                                    TablaSzerkezet amitBlokkolt = new TablaSzerkezet(ahovaLepett);
                                    amitBlokkolt.setBounds(row, column);

                                    amitBlokkolt.setJatekosTipusa(2);

                                    nodus.add(amitBlokkolt);
                                }
                            }
                        }
                    }
            }
        }
        else {
            for(int i = 0; i < 8; i++) {


                    if(szabadHely(minPlayerPos[0] + checkX[i], minPlayerPos[1] + checkY[i])) {
                        TablaSzerkezet ahovaLepett = new TablaSzerkezet(this);

                        ahovaLepett.setMinPlayer( minPlayerPos[0] + checkX[i], minPlayerPos[1] + checkY[i]);

                        for(int row = 0; row <= k+1; row++) {
                            for(int column = 0; column <= k+1; column++) {

                                if(ahovaLepett.szabadHely(row, column)) {
                                    TablaSzerkezet amitBlokkolt = new TablaSzerkezet(ahovaLepett);
                                    amitBlokkolt.setBounds(row, column);

                                    amitBlokkolt.setJatekosTipusa(1);

                                    nodus.add(amitBlokkolt);
                                }
                            }
                        }
                    }
            }
        }

        return nodus;
    }

}
