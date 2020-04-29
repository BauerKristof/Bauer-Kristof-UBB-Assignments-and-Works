package abstractFactory.scrollBars;

import bridge.abstraction.Window;
import compositeMinta.Glyph;
import compositeMinta.leaf.Point;

public class ScrollBar implements Glyph {

	private int start;
	private int end;
	private int position;

	public ScrollBar(int position) {
		this.position = position;
	}

	public void scrollTo(int position) {
		start = position;
	}

	@Override
	public String toString() {
		return "A scrollBar kezdete=" + start + ". A vege=" + end + "A pozicioja=" + position;
	}

	@Override
	public void draw(Window window) {
		window.drawCharacter(this);

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
