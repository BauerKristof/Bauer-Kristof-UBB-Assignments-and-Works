package bridge.abstraction;

import bridge.implementor.WindowImp;
import compositeMinta.Glyph;

public class Window {

	private WindowImp windowImp;
	private Glyph glyph;

	public Window(Glyph glyph, WindowImp windowImp) {
		this.glyph = glyph;
		this.windowImp = windowImp;
	}

	public void drawCharacter(Glyph character) {
		System.out.println("Kirazjolva:" + character);
	}

	public void reDraw() {
		System.out.println("Window ujrarajzolva");
	}

	public void raise() {
		windowImp.deviceRaise();
	}

	public void lwoer() {
		windowImp.deviceLower();
	}
}
