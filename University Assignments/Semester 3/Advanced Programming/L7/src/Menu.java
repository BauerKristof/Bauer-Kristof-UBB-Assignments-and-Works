public class Menu {
    private Soup soup;
    private MainDish mainDish;

    private void createMenu(Chef chef) {
        soup = chef.prepareSoup();
        mainDish = chef.prepareMainDish();
        soup.associateMainDish(mainDish);
    }

    public static void main(String[] args) {
        Menu menu = new Menu();

        menu.createMenu(new ChineseChef());
        menu.createMenu(new IndianChef());
    }

}