import HomePage from "./content/homePage/HomePage";
import ShopPage from "./content/shopPage/ShopPage";
import SalesPage from "./content/salesPage/SalesPage";
import ChatPage from "./content/chatPage/ChatPage";
import UserPage from "./content/userPage/UserPage";
import Dock from "./dock/Dock";
import ToggleTheme from "./dock/ToggleThemeButton";
import { BrowserRouter, Routes, Route } from "react-router-dom";

import { RiHomeSmileFill, RiUser5Fill } from "react-icons/ri";
import { MdDiscount } from "react-icons/md";
import { FaShop } from "react-icons/fa6";
import { IoMdChatbubbles } from "react-icons/io";

const iconSize = 25;

const items = [
  {
    icon: <RiHomeSmileFill size={iconSize} />,
    label: "Home",
    to: "/",
  },
  {
    icon: <FaShop size={iconSize} />,
    label: "Shop",
    to: "/shop",
  },
  {
    icon: <MdDiscount size={iconSize} />,
    label: "Sales",
    to: "/sales",
  },
  {
    icon: <IoMdChatbubbles size={iconSize} />,
    label: "Chat",
    to: "/chat",
  },
  {
    icon: <RiUser5Fill size={iconSize} />,
    label: "User",
    to: "/user",
  },
];

function App() {
  return (
    <BrowserRouter>
      <div className="app">
        <div className="content">
          <ToggleTheme />
          <Routes>
            <Route path="/" element={<HomePage />} />
            <Route path="/shop" element={<ShopPage />} />
            <Route path="/sales" element={<SalesPage />} />
            <Route path="/chat" element={<ChatPage />} />
            <Route path="/user" element={<UserPage />} />
          </Routes>

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
    </BrowserRouter>
  );
}

export default App;
