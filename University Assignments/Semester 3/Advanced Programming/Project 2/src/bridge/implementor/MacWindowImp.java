package bridge.implementor;

public class MacWindowImp implements WindowImp {
	public void deviceRaise() {
		System.out.println("Mac novel");
	}

	public void deviceLower() {
		System.out.println("Mac csokkent");
	}

	public void deviceCharacter() {
		System.out.println("Mac karakter");
	}
}
