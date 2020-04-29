import java.util.ArrayList;
import java.util.Scanner;

import static java.lang.System.exit;

public class Jatek {
    private TablaSzerkezet kiinduloPont;

    public Jatek(int k, int jatekosTipusa) {
        if (k % 2 == 0) {
            System.out.println("Hiba: A k paratlan kel legyen");
            exit(0);
        }

        if ((jatekosTipusa != 1) && (jatekosTipusa != 2)) {
            System.out.println("Ha jatekos kezdjen akkor 2-ot adj meg, ha az AI 1-et!");
            exit(0);
        }
        else {
            kiinduloPont = new TablaSzerkezet(k, jatekosTipusa);
        }
    }

    private int[] getMoves(TablaSzerkezet ujTabla) {
        System.out.println("Lepes:Add meg a sort vagy az oszlopot ahova lepnel");

        int[] points={0,0};
        Scanner input = new Scanner(System.in);


        while (ujTabla.szabadHely(points[0], points[1]) == false) {

            points[0] = input.nextInt();
            points[1] = input.nextInt();

            if (!ujTabla.szabadHely(points[0], points[1])) {
                System.out.println("Hibasan adtad meg az adatokat, probald ujra");
            }
        }

        return points;
    }

    private int[] getBlocks(TablaSzerkezet ujTabla) {
        System.out.println("BLOKKOLAS:Blokkolj egy mezot!");
        int[] points={0,0};
        Scanner input = new Scanner(System.in);

        while(ujTabla.szabadHely(points[0], points[1])==false) {
            points[0] = input.nextInt();
            points[1]= input.nextInt();

            if(!ujTabla.szabadHely(points[0], points[1])) {
                System.out.println("A cella mar foglalt");
            }
        }
        return points;
    }


    public void startGame() {
        generalUjTablak(kiinduloPont, 1);

        TablaSzerkezet aktualisNodus = kiinduloPont;

        while(!aktualisNodus.terminalState()) {
            if(aktualisNodus.getJatekosTipusa() == 1)
            {
                aktualisNodus = aktualisNodus.getLegjobbLepes();
                aktualisNodus.setJatekosTipusa(2);
            }
            else {
                aktualisNodus.printBoard();
                TablaSzerkezet newState = aktualisNodus;


                int[] points=getMoves(newState);
                newState.setMinPlayer(points[0],points[1]);

                points=getBlocks(newState);
                newState.setBounds(points[0], points[1]);

                for(TablaSzerkezet kovetkezoNodus : aktualisNodus.getNodus()) {
                    if(kovetkezoNodus.isEqual(newState)) {
                        aktualisNodus = kovetkezoNodus;
                        break;
                    }
                }

                aktualisNodus.setJatekosTipusa(1);
            }
        }
        aktualisNodus.printBoard();

        if(aktualisNodus.getJatekosTipusa() == 1) {
            System.out.println("Gratulalok nyertel!");
        }
        else {
            System.out.println("Sajnos nyert az AI :(");
        }

    }

    public void generalUjTablak(TablaSzerkezet jelenlegiTabla, int depth) {

        if(jelenlegiTabla.getJatekosTipusa() == 1) {

            if(jelenlegiTabla.terminalState()) {
                jelenlegiTabla.setNodusErteke(-1);
            }
            else {
                ArrayList<TablaSzerkezet> aktualisNodus = jelenlegiTabla.szamolKovLepes();

                TablaSzerkezet legjobbLepes = aktualisNodus.get(0);
                int maxTablaErtek = -1;

                for(TablaSzerkezet leszarmazottNodusok : aktualisNodus) {

                    generalUjTablak(leszarmazottNodusok, depth + 1);

                    int tablaErtek = leszarmazottNodusok.getNodusErteke();

                    if(tablaErtek > maxTablaErtek) {
                        maxTablaErtek = tablaErtek;
                        legjobbLepes = leszarmazottNodusok;
                    }
                }
                jelenlegiTabla.setNodusErteke(maxTablaErtek);
                jelenlegiTabla.setLegjobbLepes(legjobbLepes);
            }
        }
        else {
            if(jelenlegiTabla.terminalState()) {
                jelenlegiTabla.setNodusErteke(1);
            }
            else {
                ArrayList<TablaSzerkezet> children = jelenlegiTabla.szamolKovLepes();

                int minTablaErtek = 1;

                for(TablaSzerkezet child : children) {

                    generalUjTablak(child, depth + 1);

                    int tablaErtek = child.getNodusErteke();
                    if(tablaErtek < minTablaErtek) {
                        minTablaErtek = tablaErtek;
                    };
                }

                jelenlegiTabla.setNodusErteke(minTablaErtek);
            }
        }
    }

    public static void main(String[] args) throws Exception {


        Jatek g = new Jatek(3, 1);
        g.startGame();
    }
}
