public class AlmondSoup implements Soup {

    public void associateMainDish(MainDish dish) {
        //System.out.println(this.toString());
        System.out.println("A "+this.toString()+"leveshez a "+dish);
    }

    public String toString() {
        return "Almond Soup";
       // return "Az Almond Soup leveshez a Chickpea Curry foetelt tarsitottam.";
    }

}
