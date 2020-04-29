package compositeMinta.compsite;

import java.util.ArrayList;

import compositeMinta.Glyph;
import compositeMinta.leaf.Point;
import strategyMinta.Compositor;
import windowPackage.Window;

public class Composition implements Glyph {

	private Compositor compositor;
	private ArrayList<Glyph> listElements;


	public Composition(Compositor compositor) {
		listElements = new ArrayList();
		this.compositor = compositor;
	}

	public void draw(Window window) {
		for (Glyph g : listElements) {
			window.drawCharacter(g);
		}
	}

	public boolean intersects(Point point) {
		System.out.println("Ez a pont: "+point +"keresztezodik egy Glyphel!");
		return true;
	}

	public void insert(Glyph glyph, int position) {
		listElements.add(position, glyph);

	}

	public void remove(Glyph glyph) {
		listElements.remove(glyph);
	}

}
