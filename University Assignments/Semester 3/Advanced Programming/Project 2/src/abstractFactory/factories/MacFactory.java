package abstractFactory.factories;

import abstractFactory.buttons.Button;
import abstractFactory.buttons.MacButton;
import abstractFactory.scrollBars.MacScrollBar;
import abstractFactory.scrollBars.ScrollBar;

public class MacFactory implements GUIFactory {

	@Override
	public ScrollBar createScrollBar() {
		return new MacScrollBar(5);
	}

	@Override
	public Button createButton() {
		return new MacButton();
	}

}
