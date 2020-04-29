package abstractFactory.buttons;

import bridge.abstraction.Window;
import compositeMinta.Glyph;
import compositeMinta.leaf.Point;

public class Button implements Glyph {
	
	public void press() {
		System.out.println("Button Lenyomva");
	}

	@Override
	public void draw(Window window) {
		// TODO Auto-generated method stub
		
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
