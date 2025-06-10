import pandas as pd
import matplotlib.pyplot as plt

if __name__ == '__main__':
    FILEPATH = r"C:\Users\xach2\source\repos\HomeControl\HomeControl\serverLoad.txt"

    df = pd.read_csv(FILEPATH, header=None, names=["Server", "GreedyLoad", "TreeLoad"])

    df.set_index("Server")[["GreedyLoad", "TreeLoad"]].plot(
        kind="bar", figsize=(8, 5), colormap="Set2")

    plt.title("Compare")
    plt.ylabel("Total load")
    plt.xlabel("Server")
    plt.grid(True, linestyle='--', alpha=0.6)

    plt.legend(title="Method", loc="lower right")

    plt.tight_layout()
    plt.savefig("Diagram.png")
    plt.show()
