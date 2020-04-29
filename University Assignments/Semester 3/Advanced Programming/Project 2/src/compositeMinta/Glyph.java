package compositeMinta;

import bridge.abstraction.Window;
import compositeMinta.leaf.Point;

public interface Glyph {

	public void draw(Window window);
	public boolean intersects(Point point);
	public void insert(Glyph glyph,int position);
	public void remove(Glyph glyph);

}
