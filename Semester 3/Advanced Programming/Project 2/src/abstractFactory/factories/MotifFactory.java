package abstractFactory.factories;

import abstractFactory.buttons.Button;
import abstractFactory.buttons.MotifButton;
import abstractFactory.scrollBars.MotifScrollBar;
import abstractFactory.scrollBars.ScrollBar;

public class MotifFactory implements GUIFactory {

	@Override
	public ScrollBar createScrollBar() {
		return new MotifScrollBar(5);
	}

	@Override
	public Button createButton() {
		return new MotifButton();
	}

}
