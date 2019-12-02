import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.stream.Collectors;

public class main {
	private static int run(List<Integer> opcodes) {
			for (int i = 0; i < opcodes.size(); ++i) {
				switch (opcodes.get(i)) {
					case 1:
						opcodes.set(opcodes.get(i + 3), opcodes.get(opcodes.get(i + 1)) + opcodes.get(opcodes.get(i + 2)));
						i += 3;
						break;
					case 2:
						opcodes.set(opcodes.get(i + 3), opcodes.get(opcodes.get(i + 1)) * opcodes.get(opcodes.get(i + 2)));
						i += 3;
						break;
					case 99:
						return opcodes.get(0);
				}
			}
			return opcodes.get(0);
	}

	public static void main(String[] args) {
		try {
			BufferedReader reader = new BufferedReader(new FileReader("C:\\Advent-of-Code-2019\\Input II"));
			List<Integer> opcodes = Arrays.stream(reader.readLine().split(",")).map(Integer::parseInt).collect(Collectors.toList());
			System.out.println("Part I: " + run(new ArrayList<>(opcodes)));
			for (int noun = 0; noun <= 99; ++noun) {
				opcodes.set(1, noun);
				for (int verb = 0; verb <= 99; ++verb) {
					opcodes.set(2, verb);
					if (run(new ArrayList<>(opcodes)) == 19690720) {
						System.out.println("Part I: " + ((100 * noun) + verb));
					}
				}
			}
		} catch (IOException exception) {
			exception.printStackTrace();
		}
	}
}