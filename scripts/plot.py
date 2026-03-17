import pandas as pd
import seaborn as sns
import matplotlib.pyplot as plt

df = pd.read_csv("results/heatmap.csv", index_col=0)

plt.figure(figsize=(12, 8))
sns.heatmap(df, 
            cmap="RdYlBu_r",
            annot=True,
            fmt="d",
            linewidths=0.5,
            cbar_kws={'label': 'Latency (cycles)'})

plt.title("ECHOES CPU Cache Hierarchy Heatmap\n(AMD Ryzen 5 5500U)", fontsize=14)
plt.xlabel("Stride Size (bytes)")
plt.ylabel("Buffer Size")
plt.gca().invert_yaxis()
plt.tight_layout()
plt.savefig("results/heatmap.png", dpi=150)
plt.show()
print("Heatmap saved to results/heatmap.png")