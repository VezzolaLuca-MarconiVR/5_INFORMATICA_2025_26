import Navbar from "./navbar/Navbar";
import Home from "./content/home/Home";
import PixelBlast from "./Pixelblast";

function App() {
  // Dynamically get the CSS variable value
  const getCSSVariable = (variableName: string) => {
    return getComputedStyle(document.documentElement)
      .getPropertyValue(variableName)
      .trim();
  };

  return (
    <div className="app">
      <div style={{ width: "100dvw", height: "100dvh", position: "relative" }}>
        <PixelBlast
          variant="square"
          pixelSize={3}
          color={getCSSVariable("--primary")}
          patternScale={5}
          patternDensity={2}
          pixelSizeJitter={0.5}
          enableRipples={false}
          rippleSpeed={0.4}
          rippleThickness={0.02}
          rippleIntensityScale={0.5}
          liquid={false}
          liquidStrength={0.12}
          liquidRadius={1.2}
          liquidWobbleSpeed={2}
          speed={0.6}
          edgeFade={0.25}
          transparent
        />
        <div className="content">
          <Navbar />
          <Home />
        </div>
      </div>
    </div>
  );
}

export default App;
