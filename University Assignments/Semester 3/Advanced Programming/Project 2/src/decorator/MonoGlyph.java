package decorator;

import bridge.abstraction.Window;
import compositeMinta.Glyph;
import compositeMinta.leaf.Point;

public class MonoGlyph implements Glyph {

	private Glyph component;

	public MonoGlyph(Glyph component) {
		this.component = component;
	}

	@Override
	public void draw(Window window) {
		window.drawCharacter(component);

	}

	@Override
	public boolean intersects(Point point) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public void insert(Glyph glyph, int position) {
		// TODO Auto-generated method stub

	}

	@Override
	public void remove(Glyph glyph) {
		// TODO Auto-generated method stub

	}

}
