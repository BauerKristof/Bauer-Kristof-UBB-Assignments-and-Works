package lab8;

import lab8.composite.Field;
import lab8.composite.Forest;
import lab8.simple.*;

public class main {

        private Forest negyszogletu;
        private Forest marosszeki;

        private Field kaszalo;
        private Field mezo;

        public main() {
            negyszogletu = new Forest();
            marosszeki = new Forest();
            kaszalo = new Field();
            mezo = new Field();

            kaszalo.Add(new Grass());
            kaszalo.Add(new Flower());

            mezo.Add(new Flower());
            mezo.Add(new Flower());
            mezo.Add(new OakTree());


            negyszogletu.Add(kaszalo);
            negyszogletu.Add(mezo);

            marosszeki.Add(kaszalo);
            marosszeki.Add(new Flower());
            marosszeki.Add(mezo);

            System.out.println("A negyszogletu kerek erdo oxigen termelese: " + negyszogletu.getOxigenAmountPerYear());
            System.out.println("A negyszogletu kerek erdo elettartama: " + negyszogletu.getLifeTime());
            System.out.println("A negyszogletu kerek erdo reprezentacioja: "+negyszogletu.getRepresentation());

            System.out.println("A marosszeki kerek erdo oxigen termelese: " + marosszeki.getOxigenAmountPerYear());
            System.out.println("A marosszeki kerek erdo elettartalma: " + marosszeki.getLifeTime());
            System.out.println("A marosszeki kerek erdo reprezentacioja: "+marosszeki.getRepresentation());

        }




    public static void main(String[] args)
    {
        new main();
    }
}
