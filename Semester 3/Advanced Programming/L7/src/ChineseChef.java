public class ChineseChef implements Chef {
    @Override
    public Soup prepareSoup() {
        return new KlangBakKutTehShoup();
    }

    @Override
    public MainDish prepareMainDish() {
        return new KungPaoChicken();
    }
}
