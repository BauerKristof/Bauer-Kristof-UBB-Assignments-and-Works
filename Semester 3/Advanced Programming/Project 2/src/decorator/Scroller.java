package decorator;

import abstractFactory.scrollBars.ScrollBar;
import bridge.abstraction.Window;
import compositeMinta.Glyph;

public class Scroller extends MonoGlyph {

	private ScrollBar scrollBar;

	public Scroller(Glyph component, ScrollBar scrollBar) {
		super(component);
		this.scrollBar = scrollBar;

	}

	public void draw(Window window) {
		super.draw(window);
		window.drawCharacter(scrollBar);
	}

}
