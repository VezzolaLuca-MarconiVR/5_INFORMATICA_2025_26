import ListGroup from "./components/ListGroup";

function App() {
  let items = ["NY", "SF"];
  return (
    <div>
      <ListGroup items={items} heading="Cities" />
    </div>
  );
}

export default App;
