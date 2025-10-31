import Home from "./content/home/Home";
import Dock from "./dock/Dock";
import ToggleTheme from "./dock/ToggleThemeButton";

import { RiHomeSmileFill, RiUser5Fill } from "react-icons/ri";
import { MdDiscount } from "react-icons/md";
import { FaShop } from "react-icons/fa6";
import { IoMdChatbubbles } from "react-icons/io";

const iconSize = 25;

const items = [
  {
    icon: <RiHomeSmileFill size={iconSize} />,
    label: "Home",
    onClick: () => alert("Home!"),
  },
  {
    icon: <FaShop size={iconSize} />,
    label: "Shop",
    onClick: () => alert("Shop!"),
  },
  {
    icon: <MdDiscount size={iconSize} />,
    label: "Sales",
    onClick: () => alert("Sales!"),
  },
  {
    icon: <IoMdChatbubbles size={iconSize} />,
    label: "Chat",
    onClick: () => alert("Chat!"),
  },
  {
    icon: <RiUser5Fill size={iconSize} />,
    label: "User",
    onClick: () => alert("User!"),
  },
];

function App() {
  return (
    <div className="app">
      <div className="content">
        <ToggleTheme />
        <Home />
        <Dock
          items={items}
          panelHeight={50}
          baseItemSize={40}
          magnification={60}
          distance={100}
          spring={{ mass: 0.2, stiffness: 50, damping: 5 }}
        />
      </div>
    </div>
  );
}

export default App;
