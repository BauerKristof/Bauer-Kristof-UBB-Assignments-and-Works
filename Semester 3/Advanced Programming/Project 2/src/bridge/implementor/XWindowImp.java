package bridge.implementor;

public class XWindowImp implements WindowImp {
	public void deviceRaise() {
		System.out.println("XWindow novel");
	}

	public void deviceLower() {
		System.out.println("XWindow csokkent");
	}

	public void deviceCharacter() {
		System.out.println("XWindow karakter");
	}

}
