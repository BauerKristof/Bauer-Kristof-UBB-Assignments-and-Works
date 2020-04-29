package decorator;

import bridge.abstraction.Window;
import compositeMinta.Glyph;

public class Border extends MonoGlyph {
	
	public Border(Glyph component) {
		super(component);
		// TODO Auto-generated constructor stub
	}

	private void drawBorder(Window window) {

	}

	public void draw(Window window) {
		super.draw(window);
	}
}
