import java.io.*;

public class main {
	public static void main(String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader("input"));
			String line = "";
			Double totalFuelI = 0D;
			Double totalFuelII = 0D;
			while (line != null) {
				line = reader.readLine();
				if (line != null) {
					Double moduleFuel = Double.parseDouble(line);
					totalFuelI += Math.floor(moduleFuel / 3) - 2;
					while ((Math.floor(moduleFuel / 3) - 2) > 0) {
						moduleFuel = Math.floor(moduleFuel / 3) - 2;
						totalFuelII += moduleFuel;
					}
				}
			}
			System.out.println("Part I: " + totalFuelI);
			System.out.println("Part II: " + totalFuelII);
		} catch (IOException exception) {
			exception.printStackTrace();
		}
	}
}