package abstractFactory.factories;

import abstractFactory.buttons.Button;
import abstractFactory.scrollBars.ScrollBar;

public interface GUIFactory {

	public ScrollBar createScrollBar();

	public Button createButton();
}
