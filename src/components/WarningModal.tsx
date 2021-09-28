import { Alert, AlertIcon, Button, Modal, ModalBody, ModalCloseButton, ModalContent, ModalFooter, ModalHeader, ModalOverlay, useDisclosure, VStack } from "@chakra-ui/react";
import React from "react";

interface WarningModalProps {
  warnings: string[];
  isOpen: boolean;
  onOpen: () => void;
  onClose: () => void;
}

export const WarningModal: React.FC<WarningModalProps> = ({ warnings,isOpen,onClose,onOpen }) => {
  return (
    <Modal onClose={onClose} isOpen={isOpen} scrollBehavior="outside">
      <ModalOverlay />
      <ModalContent>
        <ModalHeader>Warnings</ModalHeader>
        <ModalCloseButton />
        <ModalBody><VStack>
          
            {warnings.map((warning, i) => {
              return (
                <Alert borderRadius="xl" status="warning"><AlertIcon />{warning}</Alert>
              )
            })}
        </VStack>
        </ModalBody>
        <ModalFooter>
          <Button onClick={onClose}>Close</Button>
        </ModalFooter>
      </ModalContent>
    </Modal>
  );
};
