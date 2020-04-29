public class KlangBakKutTehShoup implements Soup {

    @Override
    public void associateMainDish(MainDish dish) {
        System.out.println(this);
    }

    public String toString()
    {
        return "A KlangBakKutTeh leveshez a KungPaoChicken foetelt tarsitottam.";
    }
}
