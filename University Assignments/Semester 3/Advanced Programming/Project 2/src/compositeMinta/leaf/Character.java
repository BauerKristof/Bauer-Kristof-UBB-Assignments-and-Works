package compositeMinta.leaf;

import bridge.abstraction.Window;
import compositeMinta.Glyph;

public class Character implements Glyph {

	private char c;
	private Point balFelso;
	private Point jobbAlso;

	public Character(char c, Point balFelso, Point jobbAlso) {
		this.c = c;
		this.balFelso = balFelso;
		this.jobbAlso = jobbAlso;
	}

	@Override
	public String toString() {
	return "Karakternev:"+c;
	}

	public void draw(Window window) {
		window.drawCharacter(this);
	}

	public boolean intersects(Point point) {
		System.out.println("Az alabbi pont"+point+"keresztezodik a Glymphel a "+balFelso+" "+jobbAlso+" pont altali Glyphel!");
		return true;
	}

	public void insert(Glyph glyph, int position) {

	}

	public void remove(Glyph glyph) {

	}
}
