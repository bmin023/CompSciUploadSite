import { Button, ButtonProps } from "@chakra-ui/button";
import React, { Children } from "react";

export interface IProps {
  acceptedFileTypes?: string;
  allowMultipleFiles?: boolean;
  index: number;
  onUpload: (formData: FormData,index:number) => void;
}

export const FileUpload: React.FC<IProps & ButtonProps> = ({acceptedFileTypes,allowMultipleFiles,onUpload,children,index,...rest}) => {
  const fileInputRef = React.useRef<HTMLInputElement | null>(null);
  const formRef = React.useRef<HTMLFormElement | null>(null);

  const onClickHandler = () => {
    fileInputRef.current?.click();
  };

  const onChangeHandler = (event: React.ChangeEvent<HTMLInputElement>) => {
    if (!event.target.files?.length) {
      return;
    }

    const formData = new FormData();

    formData.append("file", event.target.files[0]);

    onUpload(formData,index);

    formRef.current?.reset();
  };

  return (
    <form ref={formRef}>
      <Button type="button" onClick={onClickHandler} {...rest}>
        {children}
      </Button>
      <input
        accept={acceptedFileTypes}
        multiple={allowMultipleFiles}
        onChange={onChangeHandler}
        ref={fileInputRef}
        style={{ display: "none" }}
        type="file"
      />
    </form>
  );
};

FileUpload.defaultProps = {
  acceptedFileTypes: ".cpp",
  allowMultipleFiles: false,
};
