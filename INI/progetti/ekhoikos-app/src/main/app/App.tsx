import Navbar from "./navbar/Navbar";
import Home from "./content/home/Home";

function App() {
  // const [var, setVar] = useState(0)

  return (
    <div className="app">
      <Navbar />
      <div className="content">
        <Home />
      </div>
    </div>
  );
}

export default App;
