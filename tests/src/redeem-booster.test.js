import "core-js/stable";
import "regenerator-runtime/runtime";
import { processTest, populateTransaction } from './test.fixture';

const contractName = "Items";
const contractAddr = "0x9c25ee0f938122a504be82189536df74687858e4";
const testNetwork = "polygon";
const chainID = 137;
const testLabel = "Redeem Booster";  // <= Name of the test
const testDirSuffix = "redeem_booster"; // <= directory to compare device snapshots to
const signedPlugin = false;

const devices = [
  {
      name: "nanos",
      label: "Nano S",
      steps: 5 + 2, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanox",
      label: "Nano X",
      steps: 5, // <= Define the number of steps for this test case and this device
  },
  {
      name: "nanosp",
      label: "Nano S+",
      steps: 5, // <= Define the number of steps for this test case and this device
  },
];

// https://polygonscan.com/tx/0x2a477ecc0a9821a097150b455f268b27f114e166a65d4bc1e7251350249614ba
const inputData = "0x1e9a6950000000000000000000000000b835f2736a2bafafb8e4a250fe130dc08b74006e00000000000000000000000000000000000000000110000361e458db33b247b5";
const serializedTx = populateTransaction(contractAddr, inputData, chainID);

devices.forEach((device) => {
  processTest(device, contractName, testLabel, testDirSuffix, "", signedPlugin, serializedTx, testNetwork);
});
