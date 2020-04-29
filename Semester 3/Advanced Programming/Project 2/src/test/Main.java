package test;

import abstractFactory.factories.GUIFactory;
import abstractFactory.factories.MacFactory;
import bridge.abstraction.Window;
import bridge.implementor.MacWindowImp;
import bridge.implementor.WindowImp;
import compositeMinta.Glyph;
import compositeMinta.compsite.Row;
import compositeMinta.leaf.Character;
import compositeMinta.leaf.Point;
import decorator.Border;
import strategyMinta.Compositor;
import strategyMinta.TeXCompositor;

public class Main {

	public static void main(String[] args) {

		Point elsoPont = new Point(3, 3);
		Point masodikPont = new Point(2, 3);
		Point harmadikPont = new Point(3, 3);
		Point negyedikPont = new Point(2, 3);
		Point otodikPont = new Point(4, 4);
		Point hatodikPont = new Point(3, 3);


		System.out.println("a-b-c Pontok letrehozasa");
		Character elsoKarakter = new Character('a', elsoPont, masodikPont);
		Character masodikKarakter = new Character('b', harmadikPont, negyedikPont);
		Character harmadikKarakter = new Character('c', otodikPont, hatodikPont);

		Compositor textcomp = new TeXCompositor();

		Glyph glyphPeldany = new Row(textcomp);
		glyphPeldany.insert(elsoKarakter, 0);
		glyphPeldany.insert(masodikKarakter, 1);
		glyphPeldany.insert(harmadikKarakter,2);



		WindowImp windowImpPeldany = new MacWindowImp();
		Window bridgePeldany = new Window(glyphPeldany, windowImpPeldany);
		bridgePeldany.raise();
		System.out.println("Pontok kirajzolasa");
		glyphPeldany.draw(bridgePeldany);

		GUIFactory abstractFactoryPeldany = new MacFactory();
		abstractFactoryPeldany.createButton();
		abstractFactoryPeldany.createScrollBar();

		System.out.println("Decorator letrehozasa");
		Glyph decorator = new Border(new Character('a', elsoPont, masodikPont));

	}

}
